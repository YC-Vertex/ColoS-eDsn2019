# ColoS-eDsn2019
Car "ColoS" of team Colossus Trio in eDsnCompetition 2019

---

## 20191101 14:30 - zyc:

### init

这里是A车的代码，当前进度：原始级别惯导完成（走直线距离），陀螺仪未调通

上层代码在`User/App/`里，目前有三个进程：`BasicTask`在`AppBasic.c`中，是主进程，priority == Normal；`SensorTask`和`EncoderTask`在`AppSensor.c`中，priority分别为AboveNormal和Realtime。上层的全局内容写在`AppConfig.c/.h`中。

底层代码在`User/Bsp/`（硬件抽象）和`User/Drv/`（模块抽象）中，初始化内容在`Src/main.c`，全局内容  在`Inc/main.h`中。

使用方法是打开`MDK-ARM/*.uvprojx`，然后编译烧录即可。

> Jim有三只巨像 / Jim出线啦 / 我可是专业解说啊
