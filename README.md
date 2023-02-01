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

## Installation Qt

Project sử dụng [Qt Framework](https://www.qt.io/) v5.12 để chạy

Cài đặt Qt trên Ubuntu

```sh
sudo apt install qt5-default
```

## Run Project
##### _1. Clone Project_ #####

```sh
git clone https://github.com/tuyenldhust/AiLaTrieuPhu.git
cd AiLaTrieuPhu
```

##### _2. Run Server_ #####

```sh
cd server/
make
./server <PORT>
```

##### _3. Run Client_ #####

```sh
cd client/
qmake
make install
./client
```
