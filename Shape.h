#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Point {//点类（基类）
protected:
	double m_x = 0;//xy坐标
	double m_y = 0;
public:
	Point() = default;//默认构造函数
	Point(double x, double y) :m_x(x), m_y(y) {}//有参构造函数
	Point(const Point& p) :m_x(p.m_x), m_y(p.m_y) {}//复制构造函数
	~Point() = default;//析构函数

	double howlong(const Point& p) const{//用于计算两点的长度,  对返回const
		if (this != &p) {//保证不是自己
			return sqrt((double)pow((m_x - p.m_x), 2) + (double)pow((m_y - p.m_y), 2));//需要转类型，保证类型一致
		}
	}
};

//当我用基类和基类的派生类比较时，依旧会比较，会造成矩形和长方体比面积等，所以要再建长度，面积，体积类用于区分

class Theline {//长度类       因为长度类中的线类有派生类，若将运算符重载放在这，三角形，矩形，长方体可能也会调用他们基类：线类 的基类之一：长度类（因此，矩形等会被划分为长度类进行长度的比较，出错）
public:
	Theline() = default;//默认构造函数
	~Theline() = default;//析构函数

	virtual double line() const = 0;//虚函数，后面 长度 再重新定义

};

class Area {//面积类                          
public:
	Area() = default;//默认构造函数
	~Area() = default;//析构函数

	virtual double area() const = 0;//虚函数，后面 面积 再重新定义

};

class Myvec;
class Volume {//体积类  
	friend Myvec;//声明Myvec类为友元，方便获取其派生类
public:
	Volume() = default;//默认构造函数
	~Volume() = default;//析构函数

	virtual double volume() const = 0;//虚函数，后面 体积 再重新定义
	virtual double getvalue() const = 0;//虚函数,用于后面获取具体派生的价值
};

class Circle :public Point,public Area {//圆类（继承点类,面积类）(圆柱，圆锥的基类)
protected:
	Point p;//点类型的圆心
	double m_radius = 0;//半径
public:
	Circle() = default;//默认构造函数
	Circle(const Point& p, double r) :Point(p), m_radius(r) {}//有参构造函数(里面用的是point类型的p来初始化point，拷贝基类)
	Circle(const Circle& c) :Point(c), m_radius(c.m_radius) {}//复制构造函数
	~Circle() = default;//析构函数

	double zhouchang() {//计算周长
		return 2 * 3.14 * m_radius;
	}

	double area() const {//虚函数，后面储蓄和基金再重新定义   派生类对其基类类型对象的protected成员没有特殊访问权限,所以在派生类的函数中通过基类的对象来访问protected成员是非法的
		return 3.14 * m_radius * m_radius;
	}
	Area& operator<(const Area& c) {//面积小于号运算符重载
		if (this != &c) {
			if (this->area() < c.area()) {
				cout << "面积：" << this->area() << "小于" << c.area() << endl;
			}
			else {
				cout << "面积：" << this->area() << "大于等于" << c.area() << endl;
			}
		}
		return *this;
	}
};

class Line :public Point,public Theline {//线类（继承点类，长度类）（三角形，矩形，长方体的基类）
protected:
	Point p1;//点类型的圆心
	Point p2;
public:
	Line() = default;//默认构造函数
	Line(const Point & p, const Point & b) :p1(p), p2(b) {}//有参构造函数
	Line(const Line & c) :p1(c.p1), p2(c.p2) {}//复制构造函数
	~Line() = default;//析构函数

	double line() const {//计算长度，由点类定义的howlong求
		return p1.howlong(p2);
	}

	Theline& operator<(const Theline& c) {//长度小于号运算符重载   
		if (this != &c) {
			if (this->line() < c.line()) {
				cout << "长度：" << this->line() << "小于" << c.line() << endl;
			}
			else {
				cout << "长度：" << this->line() << "大于等于" << c.line() << endl;
			}
		}
		return *this;
	}

};

class Delta :public Line, public Area {//三角形类（基类为线类，面积类）
protected:
	Line s;//底线
	Line h;//高
public:
	Delta() = default;//默认构造函数
	Delta(const Line& p, const  Line& b) :s(p), h(b) {}//有参构造函数
	Delta(const Delta& c) :s(c.s), h(c.h) {}//复制构造函数
	~Delta() = default;//析构函数

	double area() const {//计算三角形面积，底*高
		return (1/2)*s.line() * h.line();
	}
	Delta& operator<(const Area& c) {//面积小于号运算符重载
		if (this != &c) {
			if (this->area() < c.area()) {
				cout << "面积：" << this->area() << "小于" << c.area() << endl;
			}
			else {
				cout << "面积：" << this->area() << "大于等于" << c.area() << endl;
			}
		}
		return *this;
	}
};

class Rect :public Line, public Area {//矩形类（基类为线类，面积类）
protected:
	Line a;//长
	Line b;//宽
public:
	Rect() = default;//默认构造函数
	Rect(const Line& p, const  Line& b) :a(p), b(b) {}//有参构造函数
	Rect(const Rect& c) :a(c.a), b(c.b) {}//复制构造函数
	~Rect() = default;//析构函数

	double area() const {//计算矩形面积，长*宽
		return a.line() * b.line();
	}
	Rect& operator<(const Area& c) {//面积小于号运算符重载
		if (this != &c) {
			if (this->area() < c.area()) {
				cout << "面积：" << this->area() << "小于" << c.area() << endl;
			}
			else {
				cout << "面积：" << this->area() << "大于等于" << c.area() << endl;
			}
		}
		return *this;
	}
};

class Cub :public Line, public Volume {//长方体类（基类为线类，体积类）
protected:
	Line a;//长
	Line b;//宽
	Line h;//高
	double value;//价值
public:
	Cub() = default;//默认构造函数
	Cub(const Line& p, const Line& b, const Line& c,double v) :a(p), b(b), h(c),value(v) {} //有参构造函数
	Cub(const Cub& c) : a(c.a), b(c.b), h(c.h), value(c.value) {}//复制构造函数
	~Cub() = default;//析构函数

	double area() {//计算表面积
		return (a.line()*b.line()+a.line()*h.line()+b.line()*h.line())*2;
	}

	double volume() const {//计算长方体的体积，长*宽*高
		return a.line() * b.line() * h.line();
	}
	double getvalue() const {//获取价值
		return value;
	}
	Volume& operator<(const Volume& c) {//体积小于号运算符重载
		if (this != &c) {
			if (this->volume() < c.volume()) {
				cout << "体积：" << this->volume() << "小于" << c.volume() << endl;
			}
			else {
				cout << "体积：" << this->volume() << "大于等于" << c.volume() << endl;
			}
		}
		return *this;
	}
};

class Cylind :public Circle, public Volume {//圆柱类（基类为圆类，体积类）
protected:
	Circle s;//底面
	double h;//高
	double value;//价值
public:
	Cylind() = default;//默认构造函数
	Cylind(const Circle& p, double b, double v) : s(p), h(b), value(v) {}//有参构造函数
	Cylind(const Cylind& c) : s(c.s), h(c.h), value(c.value) {}//复制构造函数
	~Cylind() = default;//析构函数

	double area() {//计算表面积
		return s.zhouchang() * h;
	}

	double volume() const {//计算圆柱的体积，底面积*高
		return s.area() * h;
	}
	double getvalue() const {//获取价值
		return value;
	}
	Volume& operator<(const Volume& c) {//体积小于号运算符重载
		if (this != &c) {
			if (this->volume() < c.volume()) {
				cout << "体积：" << this->volume() << "小于" << c.volume() << endl;
			}
			else {
				cout << "体积：" << this->volume() << "大于等于" << c.volume() << endl;
			}
		}
		return *this;
	}
};

class Cone :public Circle, public Volume {//圆锥类（基类为圆类，体积类）
protected:
	Circle s;//底面
	double h;//高
	double value;//价值
public:
	Cone() = default;//默认构造函数
	Cone(const Circle& p, double b, double v) : s(p), h(b), value(v) {}//有参构造函数
	Cone(const Cone& c) : s(c.s), h(c.h), value(c.value) {}//复制构造函数
	~Cone() = default;//析构函数

	double area() {//计算表面积
		return (sqrt(4*3.14*3.14*h*h+s.zhouchang()) * s.zhouchang())/(4*3.14);
	}

	double volume() const {//计圆锥的体积，1/3 *底面积*高
		return s.area() * (h/3);
	}
	double getvalue() const {//获取价值
		return value;
	}
	Volume& operator<(const Volume& c) {//体积小于号运算符重载
		if (this != &c) {
			if (this->volume() < c.volume()) {
				cout << "体积：" << this->volume() << "小于" << c.volume() << endl;
			}
			else {
				cout << "体积：" << this->volume() << "大于等于" << c.volume() << endl;
			}
		}
		return *this;
	}
};
class Myvec{//自己定义的容器类
public:
	vector<const Volume*> m_array;//定义存放点基类指针的vector容器                  多用智能指针
	int m_rong = 0;//最大容器容量

	Myvec() = default;//默认构造函数
	Myvec(int n) : m_rong(n) {}//有参构造函数
	Myvec(const Myvec& c) : m_array(c.m_array),m_rong(c.m_rong) {}//复制构造函数
	~Myvec() = default;//析构函数

	int size() {
		return m_array.size();
	}
	void addthing(const Volume& p) {//添加点类的派生类  长方体，圆柱，圆锥类（给定物品的容器添加）
		m_array.push_back(&p);//将p的地址解开给vector容器内的基类指针
	}

	void tosort() {//对容器内元素按体积从小到大排序
		const Volume* s = nullptr;
		for (int i = m_array.size() - 1; i >= 0; --i)
		{
			for (int j = 0; j <= i - 1; ++j)
			{
				if (m_array[j]->volume() > m_array[j + 1]->volume())
				{
					s = m_array[j];
					m_array[j] = m_array[j + 1];
					m_array[j + 1] = s;
				}
			}
		}
	}
	void valuesort(vector<const Volume*>& array) {//对容器内元素按  价值与容量的比值   从大到小排序
		const Volume* s = nullptr;
		for (int i = array.size() - 1; i >= 0; --i)
		{
			for (int j = 0; j <= i - 1; ++j)
			{
				if ((array[j]->getvalue()/array[j]->volume()) < (array[j+1]->getvalue() / array[j+1]->volume()))
				{
					s = array[j];
					array[j] = array[j + 1];
					array[j + 1] = s;
				}
			}
		}
	}

	void toput(Myvec &a) {//将存放给定物品的容器内的物品 按要求放进来
		valuesort(a.m_array);//将存放给定物品的容器按 价值与容量的比值从大到小排序
		int nowv = 0;//用来存放现在的容量
		cout << "最优方案是：";
		for (int i = 0; i <=a.m_array.size() - 1; ++i) {//循环遍历给定容器
			if (nowv<(this->m_rong)) {//当现在目标容器的容量小于其最大容量，可继续放
				if ((nowv + a.m_array[i]->volume())<= (this->m_rong)){//如果放入该物品依旧不会超最大容量，则放入，并输出1  
					this->addthing(*a.m_array[i]);//将目前给定物品的容器的最大性价比的放入目标容器
					nowv += a.m_array[i]->volume();//将放入的物品的容器加到目前容量上
					cout << 1;
				}
				else {//否则输出0
					cout << 0;
				}
			}
			else {//若已经满了，但还没放完，则剩下的输出0
				cout << 0;
			}		
		}
	}
};
