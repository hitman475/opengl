# 变换

## 为什么要变换？

变换有两种，一种 model 和 view 变换，其中model变换中包括缩放， 而view则主要是讲3D投影到2D的画面上

## 二维变换

要找到一个变换，实际上就是寻找变换后得坐标(x‘,y’)和变换之前的坐标（x,y）之间的关系，即 x' = Mx

其中M就是变换矩阵，根据M*x就可以得到变换之后的坐标。

### 缩放（Scale）

![image-20200521211717078](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521211717078.png)

（x',y'）和（x，y）的关系写成矩阵的形式就是

![image-20200521211958898](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521211958898.png)

缩放又可以分为均匀缩放和非均匀缩放：

![image-20200521212028738](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521212028738.png)

若Sx和Sy不相等，则x轴和y轴的拉伸程度不通，最终得到的结果就是非均匀缩放。

![image-20200521212244217](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521212244217.png)

### 反射矩阵（Shear Matrix）

![image-20200521212350388](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521212350388.png)

y轴不变，将物体对y轴进行对称，则 x' = -x , y' = -y，矩阵表示如下

![image-20200521212357281](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521212357281.png)

### 切变换（Shear Matrix）

![image-20200521212622179](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521212622179.png)

改变换如图所示，物体在y轴方向上没有变化，而在x轴方向上进行了拉伸

1.在y轴上没有变化，则 y’ = y

2.y = 0 时，水平位移为0，而y = 1时，水平位移为 a，根据图可得，若y = 1/2时，则x的水平位移为 a/2

以上就可以得到（x',y'）的关系，然后根据关系写出变换：y = y,  x = x + ay

![image-20200521212859203](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521212859203.png)

### 旋转（Rotate）

默认情况下，旋转是指绕着原点，逆时针旋转

如果要实现这样一个旋转效果，应该如何做?

![image-20200521213117843](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521213117843.png)

直接给出一个旋转矩阵公式如下：

![image-20200521213440217](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521213440217.png)

即用（x',y'） = Rθ * (x,y) 就可以得到这个变换，推到如下：

用两个特殊点A,B来推导这个旋转矩阵，因为这个矩阵是通用的，所以A,B两点的变换也就应该满足这个矩阵，所以直接通过A,B推到出R

![image-20200521215100878](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521215100878.png)

推到过程如上图所示，b，d的过程类似，就不再具体的展开

![image-20200522082056071](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200522082056071.png)

旋转-θ角就是R的逆矩阵，R的逆矩阵 = R的转置 ，所旋转矩阵R是一个正交矩阵



### 线性变换（Linear Transforms = Matrices (of the same dimension)）

![image-20200521215350243](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521215350243.png)

线性变换就是：用相同维度的矩阵×变换的点  （前面两行可以看出(x,y)和（x',y'）是一种线性的关系，所以是线性变换）

符合如下形式的变换，就是线性变换

![image-20200521215406786](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521215406786.png)

### 齐次坐标（Homogeneous coordinates）

#### 为什么要引入齐次坐标？

先看下面一个变换

![image-20200521215617124](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521215617124.png)

这是一个位移的变换，其（x',y'）和（x,y）的关系如上式所示，只是通过简单的相加就能得到其变换，那么写成矩阵的形式呢？如下所示

![image-20200521215750888](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521215750888.png)

可以看到，以上的变换并不是一种线性变换，这种变换不能使用之前那种矩阵的形式来得到（x' = Mx这种形式），缩放以及旋转都可以都是一种线性变换，但是如果将位移这种变换作为一种特殊的情况，那么在应用中会带来很多麻烦。**所以这里就要引入齐次坐标**，**用来解决位移变换的这种特殊的情况，将位移变换也能够统一为**

**x' = Mx的这种形式**



#### 用齐次坐标解决上面的问题（Solution: Homogenous Coordinates）

如何用齐次坐标？给点（point）或者向量（vector）添加一个维度，即w坐标，

2D point =  (x,y,1)

2D vector = (x,y,0)

点和向量添加的w坐标不同，原因后面解释，先看怎么用w维度来对图形进行位移变换：

![image-20200521222944503](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521222944503.png)

先看两个等式中间的一个三维矩阵，该矩阵实现了图形的位移的变换，最终（x,y）都加上了位移量t，

接着看三维矩阵，可以对该三维矩阵进行一个划分，其不同部分实现不同的变换效果

1.左上角的二维矩阵

![image-20200521223141830](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521223141830.png)

改变该处的值，能够实现图形的缩放和旋转，该部分就相当于之前旋转和缩放时所使用的二维矩阵

2.右上角的2*1的矩阵

![image-20200521223248791](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521223248791.png)

此处为的值为图形的变换量，因为tx , ty 最终乘点的w分量1，最后就会讲相应的位移量添加到相应的坐标上，**此处就是通过齐次坐标来实现位移的线性变换**

3.最下面一列

![image-20200521223538470](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521223538470.png)

基本无用，保持001即可

##### 以上就是通过齐次坐标来实现点的线性位移变换，接下来讨论，为什么点和向量的w分量的值不同？

向量代表一个方向，向量即使发生了位移的变换，但是向量的方向仍然不变，并且向量也不会改变，**即向量具有位移不变性**。所以向量不论进行怎样的位移变换都不应该发生变化，所以向量的w分量为0，则位移矩阵中的位移量就不会添加到向量的x,y坐标上，也就实现了向量的位移不变性

![image-20200521224158442](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521224158442.png)





#### 2D 变换汇总

![image-20200521224253402](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521224253402.png)

#### 逆变换（Inverse Transform）

逆变换如图所示

![image-20200521224352712](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521224352712.png)

先实现了变换M，顺时针旋转并平移，如果要再将图形变回到原来的位置，则就需要使用逆变换

![image-20200521224444118](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521224444118.png)

其中M和M的逆为互逆矩阵

#### 组合变换（Composing Transform）

变换的次序应该遵守 先应用线性变换（缩放，旋转），再应用平移变换，（矩阵从右往左为变换先后顺序）， 不同的变换顺序会带来不同的效果，为什么？

因为矩阵的运算并不遵守交换律，即两个矩阵A，B相乘 ， AB != BA,所以变换矩阵相乘的次序不同，最后得到的变换效果也就不同

![image-20200521224743618](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521224743618.png)

![image-20200521230601144](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521230601144.png)

根据最终的结果判断是point还是vector，若最终结果w分量为0，则为vector，若w分量不为0，则是point，

point+point得到的结果是两个点的中点，如下：

![image-20200521230717821](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521230717821.png)

齐次坐标中点的x,y坐标为x/w,y/2，根据这个计算point + point 最终的结果就是两点的中点



#### 组合变换

如果有一系列的变换，A1,A2,...An 则可以对这些变换进行组合 得到一个最终的变换矩阵，然后用该矩阵×点即可得到一个最终的变换效果。

![image-20200521224928287](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521224928287.png)

矩阵乘法虽然不具有交换律，但是具有结合律，可以先将前面n个变换矩阵A1,A2,...An进行结合得到一个最终变换矩阵，再乘点(x,y)即可

### 分解复杂变换（Decomposing Complex Transform）

比如要实现一个变换：绕C点进行宣传

1.先将原点位移到C点

2.进行宣传

3.将原点移动到原来的位置

![image-20200521225154760](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521225154760.png)