# ColoS-eDsn2019
Car "ColoS" of team Colossus Trio in eDsnCompetition 2019

---

## 20191127 23:00 - zyc:

加了一个新文件夹`User/Svc/`，把所有非硬件的底层逻辑（Service）放进去了，比如说上位机解码、惯导等等。

代码稍微做了一点整理，把逻辑顺了一下，但还没有测试完。

**Vertex开始接锅。**

---

## 20191122 22:30 - wys & zyc:

迟来的上传。这里是初赛版本，马上做代码整理重构。

---

## 20191113 23:45 - zyc:

把蓝牙、上位机功能调通了，本地测试过，明天去连上位机测试

所有上位机信息存在了`eGlobal`和`ePlayer[2]`里面，直接读取就行

多加了几个App的文件，不过顾名思义就不多说了

`#define __DEBUG__`现在被放在了`main.h`里，然后分化出三种，`__DEBUG_1__`是低频输出（可以一直显示的），`__DEBUG_2__`是高频输出（只有在特殊测试才会用的），`__TEMP__`是当前正在测试的专用，测试完记得改掉

稍微改了改底层uart的功能，现在usart2负责debug（接蓝牙/串口），双工；usart3负责comm（板子间交互），双工；uart5负责接收上位机信号，只读

todo: 陀螺仪、lidar

---

## 20191103 03:00 - wys & zyc:

惯导基本写完了，在寝室地上调的参

现在可以旋转跳跃托马斯大回环，来给整个活

todo: 蓝牙、陀螺仪、上位机

---

## 20191102 19:30 - zyc & wys:

加入了惯导的代码（`Drv/v_MOTION.c/.h`），但是惯导的PID有一些锅

稍微修改之后是完整可用版本

---

## 20191101 14:30 - zyc:

### init

这里是A车的代码，当前进度：原始级别惯导完成（走直线距离），陀螺仪未调通

上层代码在`User/App/`里，目前有三个进程：`BasicTask`在`AppBasic.c`中，是主进程，priority == Normal；`SensorTask`和`EncoderTask`在`AppSensor.c`中，priority分别为AboveNormal和Realtime。上层的全局内容写在`AppConfig.c/.h`中。

底层代码在`User/Bsp/`（硬件抽象）和`User/Drv/`（模块抽象）中，初始化内容在`Src/main.c`，全局内容  在`Inc/main.h`中。

使用方法是打开`MDK-ARM/*.uvprojx`，然后编译烧录即可。

> Jim有三只巨像 / Jim出线啦 / 我可是专业解说啊

