import cv2
import numpy as np
import glob
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import pickle

def CalibrateCamera():
    # The number of intersections in x
    num_x = 9
    # The number of intersections in y
    num_y = 6
    # The size of the square in meters
    pattern_square_size = 0.024

    # Initialization of the arrays to store the 3D world points and the 2D image points
    object_points = []
    object_image_points = []

    object_world_points = np.zeros((7*7,3), np.float32)
    object_world_points[:,:2] = np.mgrid[0:7, 0:7].T.reshape(-1,2)
    
    object_world_points = object_world_points*pattern_square_size

    pattern_files = glob.glob("./images/*.jpg")
    print(pattern_files)

    for pattern_file in pattern_files:
        # Reading the specific images and converting it to grayscale
        pattern_img = cv2.imread(pattern_file)
        pattern_img_size = (pattern_img.shape[1], pattern_img.shape[0])
        pattern_img_gray = cv2.cvtColor(pattern_img, cv2.COLOR_BGR2GRAY)

        # Identifying the Chessboard Corners
        corner_det_result, pattern_corners = cv2.findChessboardCorners(pattern_img_gray, (num_x, num_y), None)

        if corner_det_result:
            object_points.append(object_world_points)
            object_image_points.append(pattern_corners)

            # Draw the corners
            pattern_drawn_image = cv2.drawChessboardCorners(pattern_img, (num_x, num_y), pattern_corners, corner_det_result)

            pattern_drawn_image = cv2.resize(pattern_drawn_image, (500,500))
            cv2.namedWindow("Main", cv2.WINDOW_NORMAL)
            cv2.imshow("Main", pattern_drawn_image)
            cv2.waitKey(0)
            # return True
        calib_result, cam_matrix, dist_coeff, r_vectors, t_vectors = cv2.calibrateCamera(object_points, object_image_points, pattern_img_size, None, None)
        print(calib_result, cam_matrix, dist_coeff, r_vectors, t_vectors)

        img = cv2.imread(pattern_files[5])
        dst = cv2.undistort(img, cam_matrix, dist_coeff, None, cam_matrix)
        f, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 10))
        ax1.imshow(img)
        ax1.set_title('Original Image', fontsize=15)
        ax2.imshow(dst)
        ax2.set_title('Undistorted Image', fontsize=15)
        plt.show()

        return [calib_result, cam_matrix, dist_coeff, r_vectors, t_vectors]

if __name__ == "__main__":
    calib_result, cam_matrix, dist_coeff, r_vectors, t_vectors = CalibrateCamera()

    # Persisting the camera parameters for future uses
    cam_pickle = {}
    cam_pickle["cam_matrix"] = cam_matrix
    cam_pickle["dist_coeff"] = dist_coeff
    pickle.dump(cam_pickle, open("cam_pickle.p", "wb"))
    # cap = cv2.VideoCapture(-1)
    # cap.set(3,640)
    # cap.set(4,480)
    # while True:
    #     ret, frame = cap.read()

    #     if cv2.waitKey(2) & 0xFF == ord('q'):
    #         break

    # cap.release()
    pickle_in = open("cam_pickle.p", "rb")
    cam_data = pickle.load(pickle_in)
    print(cam_data)
    cv2.destroyAllWindows()
