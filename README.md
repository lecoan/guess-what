# 程序说明

基于C++程序设计语言实现的简单猜词游戏，一共分为三个版本。
每个版本都是在原有基础上进行一定程度的修改并添加一些新的功能。

## 注意事项

由于代码编写过程中使用了pthread.h sys/socket.h等Linux下的头文件，所以程序无法在Windows平台上通过编译

## 版本一

### 实现功能

- 用户的登陆与注册
- 用户数据的存储与读取
- 出题者可向题库中添加单词
- 玩家随机获取词库中的单词并回答
- 出题或答题成功可获得经验值
- 用户可根据用户名查找用户
- 用户可根据用户属性组合查找用户

### 代码功能划分

- **模型层** module.h moudule.cpp
- **控制层** controller.h controller.cpp
- **视图层** view.h view.cpp

#### 各模块作用

- **模型层** 
  对用户对象进行基本的抽象化，并实现service子层来简化对模型的操作
- **控制层** 
  实现程序中如登陆注册等基本任务
- **视图层** 
  向控制层传递数据并根据控制层返回的结果来展示界面

## 版本二

### 新增功能

- 系统自带题库
- 根据用户的等级来获取对应难度的单词
- 根据用户的等级适当的增加单词的数量
- 根据用户的等级适当的减少单词显示的时间

### 代码功能划分

- **模型层** module.h moudule.cpp
- **控制层** controller.h controller.cpp
- **视图层** view.h view.cpp

#### 各模块作用

- **模型层** 
  对用户对象进行基本的抽象化，并实现service子层来简化对模型的操作
- **控制层** 
  实现程序中如登陆注册等基本任务
- **视图层** 
  向控制层传递数据并根据控制层返回的结果来展示界面

## 版本三

### 新增功能

- 将程序分解成服务器与客户端
- 实现多用户同时登陆
- 服务器可同时接受个客户端的连接
- 登陆用户可查看当前所有在线用户
- 增加双人对战模式

### 代码功能划分(server)

- **模型层** module.h moudule.cpp
- **套接字层** socket.h socket.cpp

#### 各模块作用

- **模型层** 
  对用户对象进行基本的抽象化，并实现service子层来简化对模型的操作
- **套接字层** 
  对socket.h中的函数进行封装，同时提供NetHelper对象对客户端发生来的各种命令进行处理

### 代码功能划分(client)

- **模型层** module.h moudule.cpp
- **控制层** controller.h controller.cpp
- **视图层** view.h view.cpp
- **套接字层** socket.h socket.cpp

#### 各模块作用

- **模型层** 
  对用户对象进行基本的抽象化，移除service子层
- **控制层** 
  实现程序中如登陆注册等基本任务
- **视图层** 
  向控制层传递数据并根据控制层返回的结果来展示界面
- **套接字层** 
  对socket.h中的函数进行封装，提供NetHelper对象向客户端送各种请求