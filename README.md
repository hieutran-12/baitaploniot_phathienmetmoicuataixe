Phát hiện Buồn ngủ với YOLOv5
 
Kho lưu trữ này bao gồm một hệ thống phát hiện buồn ngủ dựa trên YOLOv5. Bạn có thể truy cập kho lưu trữ gốc [tại đây](https://github.com/ultralytics/yolov5)
 
 
1. Chuẩn bị Bộ dữ liệu Tùy chỉnh
Một bộ dữ liệu tùy chỉnh đã được chuẩn bị cho dự án này. Video được quay từ 21 người khác nhau trong các kịch bản có thể xảy ra khi lái xe. Ba danh mục khác nhau đã được đề cập trong các video này: bình thường, ngáp và vị trí đầu. Các điều kiện ánh sáng khác nhau và việc sử dụng kính đã được tính đến. Tổng cộng có 63 video được thu thập và gán nhãn theo phương pháp được sử dụng.

A custom data set was prepared for this project. Videos were taken from 21 different people in scenarios that could happen while driving. Three different categories were discussed in these videos: normal, yawning and head position. Various light conditions and the use of glasses were taken into account. A total of 63 videos were obtained and labeling was done according to the method to be used.


2. Giai đoạn Gán nhãn
Phần mềm LabelImg có thể được sử dụng để gán nhãn trong các dự án sử dụng phương pháp phát hiện đối tượng. Phần mềm này hỗ trợ các định dạng PASCAL VOC, YOLO và CreateML. Vì dự án này sử dụng YOLOv5 để huấn luyện, dữ liệu được gán nhãn dưới dạng tệp .txt. Không nên sử dụng các ký tự tiếng Thổ Nhĩ Kỳ trong nhãn.

2.1 Cài đặt LabelImg trên Windows
Lấy kho lưu trữ


**Get repo**
 
 `git clone https://github.com/tzutalin/labelImg.git`

**After creating and activating the virtual or anaconda environment, the following lines of code are run on the cmd screen.**

`pip install PyQt5`

`pip install lxml`

`pyrcc5 -o libs/resources.py resources.qrc`

Chạy lệnh dưới đây để mở LabelImg. Đối với lần sử dụng sau, chỉ cần thực hiện bước cuối cùng này.

`python labelImg.py`

Lưu ý: Sau khi cài đặt LabelImg, tệp predefined_classes.txt trong thư mục dữ liệu có thể được làm trống hoặc ghi các lớp sẽ sử dụng để tránh lỗi trong quá trình gán nhãn.

![predefined_classes](https://user-images.githubusercontent.com/73580507/159132999-55ba4f21-48c3-40d6-a70d-9a3431de3bfb.png)

Có tổng cộng 1.975 hình ảnh được gán nhãn để huấn luyện mô hình. 80% dữ liệu được dùng để huấn luyện và 20% để kiểm tra. Dữ liệu được chia thành 4 lớp: "bình thường", "buồn ngủ", "buồn ngủ #2" và "ngáp".

"buồn ngủ" bao gồm mắt nhắm nhưng đầu thẳng.
"buồn ngủ #2" bao gồm đầu gục xuống. Việc phân loại này giúp mô hình không đưa ra quyết định sai.
3. Giai đoạn Huấn luyện
Thuật toán YOLOv5 được chọn vì có thể cho kết quả chính xác cao ngay cả với ít dữ liệu. Ngoài ra, mô hình Nano có thể chạy trên các thiết bị nhúng và chiếm ít bộ nhớ. Cấu trúc thư mục dữ liệu phải như sau:


![data_format](https://user-images.githubusercontent.com/73580507/159135000-635c7787-81eb-4c70-a2b6-47c0f54bdcc8.png)


3.1 Chỉnh sửa tệp YAML
Tệp data.yaml chứa số lượng và tên nhãn, đường dẫn đến dữ liệu huấn luyện và kiểm tra. Tệp này cần nằm trong thư mục yolov5/data.


![data_yaml](https://user-images.githubusercontent.com/73580507/159135929-206f18ec-e1fd-4281-bb69-d24bc425d3cd.png)

Giá trị nc trong tệp yolov5n_drowsy.yaml được chỉnh thành 4 vì nó đại diện cho số lớp. Tệp này cần nằm trong thư mục yolov5/models.

3.2 Huấn luyện mô hình

```
python train.py  --resume --imgsz 640 --batch 16 --epochs 600 --data data/data.yaml --cfg models/yolov5n_drowsy.yaml --weights weights/yolov5n.pt  --name drowsy_result  --cache --device 0
```
Quá trình huấn luyện hoàn tất khi mô hình đạt hiệu suất tốt nhất tại epoch 173.

4. Phát hiện Buồn ngủ với Mô hình Đã Huấn luyện
bash
```
python drowsy_detect.py --weights runs/train/drowsy_result/weights/best.pt --source data/drowsy_training/test/images --hide-conf
```

Bạn có thể tham khảo tệp [drowsy_training_with_yolov5.ipynb] để biết thêm chi tiết về huấn luyện.(https://github.com/suhedaras/Drowsiness-Detection-with-YoloV5/blob/main/drowsy_training_with_yolov5.ipynb) for training**


## 5. Result

### 5.1 Approach 1


   ![app1](https://user-images.githubusercontent.com/73580507/159136371-943b6761-0a8f-44af-a471-ff0b78d18514.gif)
   
![frame02-1072](https://user-images.githubusercontent.com/73580507/159136614-4a2a4509-e354-4df2-9455-cb01f339e317.jpg)![frame02-2132](https://user-images.githubusercontent.com/73580507/159136623-c5deb6c9-9e69-4166-a8c3-828a30b157c0.jpg)


### 5.2 Approach 2


   ![nhtu](https://user-images.githubusercontent.com/73580507/159136464-5e057cc1-fc47-4dc0-be63-1bccd94028c6.gif) 

![frame13-1120](https://user-images.githubusercontent.com/73580507/159136568-20e91a0a-8b6f-4e97-8ec5-dbad7bb624bc.jpg)![frame13-2006](https://user-images.githubusercontent.com/73580507/159136580-4707b37d-47e2-4063-90f3-18d1cb500b05.jpg)




