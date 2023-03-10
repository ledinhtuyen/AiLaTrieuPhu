# Milionaire
## _Ai là triệu phú_
[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

Ai là triệu phú là 1 project của môn Lập trình mạng IT4062

## Features

- Đăng ký, đăng nhập, đổi mật khẩu
- Chơi 1 mình
- Chơi PvP

## Tech

Project sử dụng:
- C/C++: Ngôn ngữ dùng để xử lý phía BackEnd
- QML: Ngôn ngữ FrontEnd của Client
- Qt Framework 5.12
- MySQL: Lưu trữ tài khoản và câu hỏi

## Installation Qt

Project sử dụng [Qt Framework](https://www.qt.io/) v5.12.8 để chạy

Cài đặt Qt trên Ubuntu 20.04 hoặc cài đặt phiên bản 5.12.8 trên trang chủ của [Qt](https://www.qt.io/)

```sh
sudo apt install qt5-default
```

## Run Project
##### _1. Clone Project_ #####

```sh
git clone https://github.com/tuyenldhust/AiLaTrieuPhu.git
cd AiLaTrieuPhu
```

#### _2. Server_ ####

##### 2.1. Cài đặt MYSQL Server, library Dev MySQL #####
```sh
sudo apt install mysql-server libmysqlclient-dev
```

##### 2.2. Config file config và import database.sql #####

##### 2.3. Run Server #####

```sh
cd server/
make
./server <PORT>
```

#### _3. Client_ ####

##### 3.1. Install Lib GL #####

```sh
sudo apt install libgl1-mesa-dev
```

##### 3.2. Run Client #####

```sh
cd client/
qmake
make install
./client <ip server> <port>
```

## Demo
#### Đăng ký, Đăng nhập
![image](https://user-images.githubusercontent.com/19906050/224227476-ea8f96bf-460e-4242-8b6f-4fd7e15c8943.png)![image](https://user-images.githubusercontent.com/19906050/224227700-723a954d-93b6-4c08-9243-8c391236997b.png)
#### Menu Game
![image](https://user-images.githubusercontent.com/19906050/224227594-34ea50c7-8b1d-4c9c-b568-a1b3662e6e79.png)
#### Chế độ chơi 1 mình
![image](https://user-images.githubusercontent.com/19906050/224228120-eb16e341-b86e-431d-b465-923bff1bb241.png)![image](https://user-images.githubusercontent.com/19906050/224228783-14a90032-1a39-46db-80be-0dd95a904e24.png)

#### Quyền trợ giúp tư vấn tại chỗ
![image](https://user-images.githubusercontent.com/19906050/224228516-72b8a37b-ebed-4bea-9899-2050ba0fd375.png)
#### Thi đấu online
![image](https://user-images.githubusercontent.com/19906050/224228655-ddc19cc5-ce6f-44ad-b4f4-c5533c98f64e.png)![image](https://user-images.githubusercontent.com/19906050/224228702-d0eb971c-1b4e-4346-8af7-a79b0fe6ccc1.png)![image](https://user-images.githubusercontent.com/19906050/224228854-6d282b1f-7afb-4230-92b3-b37dc5e31917.png)![image](https://user-images.githubusercontent.com/19906050/224228916-5fcf326e-68eb-4f59-ac11-e64f8160858b.png)
![image](https://user-images.githubusercontent.com/19906050/224228932-7c69a04d-be09-440d-a27f-2cab2cb75707.png)





