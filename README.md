# SJ-keyboard
自定义旋钮小键盘

基于ATMEGA32U4主控的自定义旋钮小键盘，命名SJ-keyboard

材料清单：
arduino pro micro *1
ec11编码器 *1
键轴、键帽 *9
总成本不超过50元

9个键可以随意设置任意按键，快捷键；
旋转编码器可以通过HID协议直接驱动win10系统下多轴控制器的滚轮设备，可实现音量，亮度的控制，模拟鼠标滚轮等。

使用到了arduino的HID-Project库：https://github.com/NicoHood/HID
源码同样参考HID-Project库提供的源码

为了方便走线与焊接，直接调用了arduino的上拉电阻，把键盘的两个触点直接短接就ok

SJ-Dial是SJ-keyboard无键盘版，根据自己需求选择

图文教程：https://www.coolapk.com/feed/20547519?shareKey=OGJiYTEzMzI1ZDQ2NWYyMjkwYTk~&shareUid=3039774&shareFrom=com.coolapk.market_10.4
