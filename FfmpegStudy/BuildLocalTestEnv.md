# 搭建本地直播测试环境

## 1. 可选方案
- ffmpeg 自带的 ffserver
    + 优点： 简单
    + 缺点，新版 ffmpeg 已经移除了 ffserver 模块
    + 最后一版还没移除 ffserver 的源码是： https://github.com/FFmpeg/FFmpeg/releases/tag/n3.4.5
- RED5
    + 特点：采用Java开发开源的Flash流媒体服务器，支持 FLV, F4V, MP4, 3GP 几种视频格式，支持 RTMP, RTMPT, RTMPS 和 RTMPE 几种协议
    + 下载地址：https://github.com/Red5/red5-server
- Darwin Streaming Server
    + https://github.com/macosforge/dss
- EasyDarwin
    + 国内商业公司基于 Darwin Streaming Server 使用 golang 开发的直播服务器。不支持 Mac 安装
    + 好处是有中文文档，坏处是文档不够详细，配置起来还得去翻代码看配置项怎么写

为了快速搭建，选择了 ffserver

## 2. 使用 ffserver 搭建直播测试环境
- 下载源码，编译和启动： 
```shell
    git clone https://github.com/FFmpeg/FFmpe
    cd FFmpeg
    ./confgure
    make
    ffserver -f server.conf
```
- 配置 server.conf
```
Port 18080
RTSPPort 28080
BindAddress 0.0.0.0

<Stream test.mp4>
Format rtp
File "/Users/zhangtianjiu/Projects/video_proj/ffserver/data/test.mpg"
</Stream>
```