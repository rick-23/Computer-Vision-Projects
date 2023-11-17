import cv2
import matplotlib.pyplot as plt
import numpy as np
from numpy.core.numeric import indices

confidence_threshold = 0.45
nms_threshold = 0.2

classLabels = []
classLabels_file_name = './Object_Labels.txt'
with open(classLabels_file_name, 'rt') as fpt:
    classLabels = fpt.read().rstrip('\n').split('\n')

# Change the paths to full paths when deploying on RP
config_file = './ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt'
weights_file = './frozen_inference_graph.pb'

model = cv2.dnn_DetectionModel(weights_file, config_file)

model.setInputSize(320,320)
model.setInputScale(1.0/ 127.5)
model.setInputMean((127.5, 127.5, 127.5))
model.setInputSwapRB(True)

def getObjects(img_frame, draw=True, objects=[]):
    font_scale = 3
    font = cv2.FONT_HERSHEY_PLAIN
    if len(objects) == 0:
        objects = classLabels
    objectInfo = []
    class_index, confidence, bbox = model.detect(frame, confThreshold=confidence_threshold, nmsThreshold=nms_threshold)
    if(len(class_index)!=0):
        for classIndex, conf, box in zip(class_index.flatten(), confidence.flatten(), bbox):
            if (classIndex<=91):
                className = classLabels[classIndex-1]
                if className in objects:
                    objectInfo.append([box, className])    
                    if(draw):
                        cv2.rectangle(frame, box, (255, 0, 0), 2)
                        cv2.putText(frame, className, (box[0]+10, box[1]+40), font, font_scale, color=(255, 0, 0), thickness=2)
    return frame,objectInfo 

if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    cap.set(3,640)
    cap.set(4,480)
    while True:
        ret, frame = cap.read()
        result, objectInfo = getObjects(frame)
        cv2.imshow("DL_Object_Detection", frame)
    
        if cv2.waitKey(2) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
