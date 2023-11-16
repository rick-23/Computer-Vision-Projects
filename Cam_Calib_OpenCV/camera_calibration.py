import cv2
import numpy as np
import glob
import sys

# The parameters
num_rows = 9
num_cols = 6
pattern_dim = 25 #mm

workingFolder   = "."
imageType       = 'jpg'

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, pattern_dim, 0.001)

if len(sys.argv) < 2:
        print("Not enough inputs are provided. Using the default values.\n")
else:
    workingFolder   = sys.argv[1]
    imageType       = sys.argv[2]

# preparing the data structure for object points (xyz) (0,0,0), (1,0,0), (2,0,0) ...
objpoints = np.zeros((num_rows*num_cols,3), np.float32)
objpoints[:,:2] = np.mgrid[0:num_cols,0:num_rows].T.reshape(-1,2)

# Arrays that store object points and image points from all the images.
object_points = [] # 3d point in real world space
img_points = [] # 2d points in image plane.

# Find the images files
images = glob.glob('./images/*.jpg')
print(len(images))
if len(images) < 9:
    print("Not enough images were found: at least 9 shall be provided!!!")
    sys.exit()
else:
    pattern_track_count = 0
    unusable_image = images[1]

    for img in images:
        pattern_img = cv2.imread(img)
        pattern_img_gray = cv2.cvtColor(pattern_img, cv2.COLOR_BGR2GRAY)

        print("Processing image", img)

        # Finding the Chess board corners
        ret, corners = cv2.findChessboardCorners(pattern_img_gray, (num_rows,num_cols), None)

        # If found, add these points to the object and image points arrays
        if ret == True:
            print("Pattern Recognized! Press ESC to skip or ENTER to accept")
             #--- Sometimes, Harris cornes fails with crappy pictures, so
            corners2 = cv2.cornerSubPix(pattern_img_gray,corners,(11,11),(-1,-1),criteria)

            # Drawing and displaying the corners
            cv2.drawChessboardCorners(pattern_img, (num_rows, num_cols), corners2, ret)
            cv2.imshow('Pattern Image', pattern_img)
            # cv2.waitKey(0)
            k = cv2.waitKey(0) & 0xFF
            if k == 27: #-- ESC Button
                print("Image Skipped")
                unusable_image = img
                continue

            print("Image accepted")
            pattern_track_count += 1
            object_points.append(objpoints)
            img_points.append(corners2)

            # cv2.waitKey(0)
        else:
            unusable_image = img


cv2.destroyAllWindows()

if(pattern_track_count > 1):
    print("Found %d good images" % (pattern_track_count))
    ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(object_points, img_points, pattern_img_gray.shape[::-1], None, None)

    # Undistorting an image
    test_undist_image = cv2.imread(unusable_image)
    h,w = test_undist_image.shape[:2]

    print("Image to undistort:", test_undist_image)

    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

    mapx, mapy = cv2.initUndistortRectifyMap(mtx, dist, None, newcameramtx, (w,h), 5)
    dst = cv2.remap(test_undist_image, mapx, mapy, cv2.INTER_LINEAR)

    # crop the image
    x,y,w,h = roi
    dst = dst[y:y+h, x:x+w]
    print("ROI: ", x, y, w, h)

    cv2.imwrite(workingFolder + "/calib_result.png", dst)
    print("Calibration Matrix: ")
    print(mtx)
    print("Disortion: ", dist)

     #--------- Save result
    filename = workingFolder + "/cameraMatrix.txt"
    np.savetxt(filename, mtx, delimiter=',')
    filename = workingFolder + "/cameraDistortion.txt"
    np.savetxt(filename, dist, delimiter=',')

else:
    print("In order to calibrate you need at least 9 good pictures... try again")
