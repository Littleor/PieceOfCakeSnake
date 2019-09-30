# 贪吃蛇小游戏 
> 最近在学习C,所以做一个纯C打造的贪吃蛇终端小游戏,由于MAC上windows的API都无法调用,所以寻找到了[ncurses](http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/)来实现控制终端.  
## 使用的技术 
* C 
* Ncurses 
## 实现效果(在src文件夹下)
* 游戏准备界面:  
![准备界面](/src/waitgame.png)  
* 游戏中界面: 
![游戏中界面](/src/game.png) 
* 游戏结束界面:
![游戏结束界面](/src/gameover.png)  
## 小结 
在实现MAC上写终端贪吃蛇的时候遇到了很多问题,最重要的就是这个库的问题了,安装Ncurses一直报错,直到看到[这篇文章](https://rhardih.io/2010/04/using-ncurses-in-c-for-text-user-interfaces-featuring-xcode/)才学会了在MAC上使用Ncurses.在此感谢这篇文章的作者.
也正是因此,我自己也写了一篇小博文来记录我的点滴:[点我前往](https://blog.sixming.com/index.php/archives/26/)
> 可以试试 QQ交流群：826352486 
> 声明: 用纯C写贪吃蛇只是为了学习交流,也让更多学C的新生能少走弯路,所以源代码大多打了注释,如有问题可以加交流群沟通.
