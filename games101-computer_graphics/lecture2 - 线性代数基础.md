## 向量的点乘

![image-20200521143949887](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521143949887.png)

### 在图形学中，点乘的作用：

1. 能够计算两个向量之间的角度，例如计算曲面和曲线之间的角度，用于计算两个方向向量之间距离有多近，越近其cos值越大，越小则越远，值为-1~1.
2. 能够将一个向量投影到另一个向量

![image-20200521144126837](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521144126837.png)

b投影到a上， 则 b的投影 = k*a，其中k是b在a上投影的长度，而用投影向量的长度再乘以a，就能得到以a为方向的b的投影

3.可以用于向量的分解，比如将一个向量分解到两个方向上

![image-20200521144413430](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521144413430.png)

4. 决定向量是指向前还是指向后方

![image-20200521144449437](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521144449437.png)

假设a为前方，则b和a的点乘值>0，b指向前方；而c和a的点乘的值<0，则c指向后方

## 向量的叉乘

#### Cross product is orthogonal to two initial vectors

#### Direction determined by right-hand rule

#### Useful in constructing coordinates systems(later)

### 叉乘在图形学中的作用

##### 1.决定向量的左(逆时针)、右(顺时针)

![image-20200521144907997](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521144907997.png)

用右手定则，从a到b为顺时针，b在a的左边；b到a为顺时针，a在b的右边

##### 2.Determine inside / outside

![image-20200521145128045](C:\Users\Southcian\AppData\Roaming\Typora\typora-user-images\image-20200521145128045.png)

e.g 判断点P是否在三角形的内部，用右手定则，AP在AB的左边，BP在BC的左边，CA在CP的左边，所以点P在ABC的内部，（*P全在右边也是内部）。但是若是 *P所在的左右不同，那么就说明P不在ABC的内部。（用来判定技能的作用范围）

