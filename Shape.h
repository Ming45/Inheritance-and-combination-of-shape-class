#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Point {//���ࣨ���ࣩ
protected:
	double m_x = 0;//xy����
	double m_y = 0;
public:
	Point() = default;//Ĭ�Ϲ��캯��
	Point(double x, double y) :m_x(x), m_y(y) {}//�вι��캯��
	Point(const Point& p) :m_x(p.m_x), m_y(p.m_y) {}//���ƹ��캯��
	~Point() = default;//��������

	double howlong(const Point& p) const{//���ڼ�������ĳ���,  �Է���const
		if (this != &p) {//��֤�����Լ�
			return sqrt((double)pow((m_x - p.m_x), 2) + (double)pow((m_y - p.m_y), 2));//��Ҫת���ͣ���֤����һ��
		}
	}
};

//�����û���ͻ����������Ƚ�ʱ�����ɻ�Ƚϣ�����ɾ��κͳ����������ȣ�����Ҫ�ٽ����ȣ�������������������

class Theline {//������       ��Ϊ�������е������������࣬������������ط����⣬�����Σ����Σ����������Ҳ��������ǻ��ࣺ���� �Ļ���֮һ�������ࣨ��ˣ����εȻᱻ����Ϊ��������г��ȵıȽϣ�����
public:
	Theline() = default;//Ĭ�Ϲ��캯��
	~Theline() = default;//��������

	virtual double line() const = 0;//�麯�������� ���� �����¶���

};

class Area {//�����                          
public:
	Area() = default;//Ĭ�Ϲ��캯��
	~Area() = default;//��������

	virtual double area() const = 0;//�麯�������� ��� �����¶���

};

class Myvec;
class Volume {//�����  
	friend Myvec;//����Myvec��Ϊ��Ԫ�������ȡ��������
public:
	Volume() = default;//Ĭ�Ϲ��캯��
	~Volume() = default;//��������

	virtual double volume() const = 0;//�麯�������� ��� �����¶���
	virtual double getvalue() const = 0;//�麯��,���ں����ȡ���������ļ�ֵ
};

class Circle :public Point,public Area {//Բ�ࣨ�̳е���,����ࣩ(Բ����Բ׶�Ļ���)
protected:
	Point p;//�����͵�Բ��
	double m_radius = 0;//�뾶
public:
	Circle() = default;//Ĭ�Ϲ��캯��
	Circle(const Point& p, double r) :Point(p), m_radius(r) {}//�вι��캯��(�����õ���point���͵�p����ʼ��point����������)
	Circle(const Circle& c) :Point(c), m_radius(c.m_radius) {}//���ƹ��캯��
	~Circle() = default;//��������

	double zhouchang() {//�����ܳ�
		return 2 * 3.14 * m_radius;
	}

	double area() const {//�麯�������洢��ͻ��������¶���   ���������������Ͷ����protected��Աû���������Ȩ��,������������ĺ�����ͨ������Ķ���������protected��Ա�ǷǷ���
		return 3.14 * m_radius * m_radius;
	}
	Area& operator<(const Area& c) {//���С�ں����������
		if (this != &c) {
			if (this->area() < c.area()) {
				cout << "�����" << this->area() << "С��" << c.area() << endl;
			}
			else {
				cout << "�����" << this->area() << "���ڵ���" << c.area() << endl;
			}
		}
		return *this;
	}
};

class Line :public Point,public Theline {//���ࣨ�̳е��࣬�����ࣩ�������Σ����Σ�������Ļ��ࣩ
protected:
	Point p1;//�����͵�Բ��
	Point p2;
public:
	Line() = default;//Ĭ�Ϲ��캯��
	Line(const Point & p, const Point & b) :p1(p), p2(b) {}//�вι��캯��
	Line(const Line & c) :p1(c.p1), p2(c.p2) {}//���ƹ��캯��
	~Line() = default;//��������

	double line() const {//���㳤�ȣ��ɵ��ඨ���howlong��
		return p1.howlong(p2);
	}

	Theline& operator<(const Theline& c) {//����С�ں����������   
		if (this != &c) {
			if (this->line() < c.line()) {
				cout << "���ȣ�" << this->line() << "С��" << c.line() << endl;
			}
			else {
				cout << "���ȣ�" << this->line() << "���ڵ���" << c.line() << endl;
			}
		}
		return *this;
	}

};

class Delta :public Line, public Area {//�������ࣨ����Ϊ���࣬����ࣩ
protected:
	Line s;//����
	Line h;//��
public:
	Delta() = default;//Ĭ�Ϲ��캯��
	Delta(const Line& p, const  Line& b) :s(p), h(b) {}//�вι��캯��
	Delta(const Delta& c) :s(c.s), h(c.h) {}//���ƹ��캯��
	~Delta() = default;//��������

	double area() const {//�����������������*��
		return (1/2)*s.line() * h.line();
	}
	Delta& operator<(const Area& c) {//���С�ں����������
		if (this != &c) {
			if (this->area() < c.area()) {
				cout << "�����" << this->area() << "С��" << c.area() << endl;
			}
			else {
				cout << "�����" << this->area() << "���ڵ���" << c.area() << endl;
			}
		}
		return *this;
	}
};

class Rect :public Line, public Area {//�����ࣨ����Ϊ���࣬����ࣩ
protected:
	Line a;//��
	Line b;//��
public:
	Rect() = default;//Ĭ�Ϲ��캯��
	Rect(const Line& p, const  Line& b) :a(p), b(b) {}//�вι��캯��
	Rect(const Rect& c) :a(c.a), b(c.b) {}//���ƹ��캯��
	~Rect() = default;//��������

	double area() const {//��������������*��
		return a.line() * b.line();
	}
	Rect& operator<(const Area& c) {//���С�ں����������
		if (this != &c) {
			if (this->area() < c.area()) {
				cout << "�����" << this->area() << "С��" << c.area() << endl;
			}
			else {
				cout << "�����" << this->area() << "���ڵ���" << c.area() << endl;
			}
		}
		return *this;
	}
};

class Cub :public Line, public Volume {//�������ࣨ����Ϊ���࣬����ࣩ
protected:
	Line a;//��
	Line b;//��
	Line h;//��
	double value;//��ֵ
public:
	Cub() = default;//Ĭ�Ϲ��캯��
	Cub(const Line& p, const Line& b, const Line& c,double v) :a(p), b(b), h(c),value(v) {} //�вι��캯��
	Cub(const Cub& c) : a(c.a), b(c.b), h(c.h), value(c.value) {}//���ƹ��캯��
	~Cub() = default;//��������

	double area() {//��������
		return (a.line()*b.line()+a.line()*h.line()+b.line()*h.line())*2;
	}

	double volume() const {//���㳤������������*��*��
		return a.line() * b.line() * h.line();
	}
	double getvalue() const {//��ȡ��ֵ
		return value;
	}
	Volume& operator<(const Volume& c) {//���С�ں����������
		if (this != &c) {
			if (this->volume() < c.volume()) {
				cout << "�����" << this->volume() << "С��" << c.volume() << endl;
			}
			else {
				cout << "�����" << this->volume() << "���ڵ���" << c.volume() << endl;
			}
		}
		return *this;
	}
};

class Cylind :public Circle, public Volume {//Բ���ࣨ����ΪԲ�࣬����ࣩ
protected:
	Circle s;//����
	double h;//��
	double value;//��ֵ
public:
	Cylind() = default;//Ĭ�Ϲ��캯��
	Cylind(const Circle& p, double b, double v) : s(p), h(b), value(v) {}//�вι��캯��
	Cylind(const Cylind& c) : s(c.s), h(c.h), value(c.value) {}//���ƹ��캯��
	~Cylind() = default;//��������

	double area() {//��������
		return s.zhouchang() * h;
	}

	double volume() const {//����Բ��������������*��
		return s.area() * h;
	}
	double getvalue() const {//��ȡ��ֵ
		return value;
	}
	Volume& operator<(const Volume& c) {//���С�ں����������
		if (this != &c) {
			if (this->volume() < c.volume()) {
				cout << "�����" << this->volume() << "С��" << c.volume() << endl;
			}
			else {
				cout << "�����" << this->volume() << "���ڵ���" << c.volume() << endl;
			}
		}
		return *this;
	}
};

class Cone :public Circle, public Volume {//Բ׶�ࣨ����ΪԲ�࣬����ࣩ
protected:
	Circle s;//����
	double h;//��
	double value;//��ֵ
public:
	Cone() = default;//Ĭ�Ϲ��캯��
	Cone(const Circle& p, double b, double v) : s(p), h(b), value(v) {}//�вι��캯��
	Cone(const Cone& c) : s(c.s), h(c.h), value(c.value) {}//���ƹ��캯��
	~Cone() = default;//��������

	double area() {//��������
		return (sqrt(4*3.14*3.14*h*h+s.zhouchang()) * s.zhouchang())/(4*3.14);
	}

	double volume() const {//��Բ׶�������1/3 *�����*��
		return s.area() * (h/3);
	}
	double getvalue() const {//��ȡ��ֵ
		return value;
	}
	Volume& operator<(const Volume& c) {//���С�ں����������
		if (this != &c) {
			if (this->volume() < c.volume()) {
				cout << "�����" << this->volume() << "С��" << c.volume() << endl;
			}
			else {
				cout << "�����" << this->volume() << "���ڵ���" << c.volume() << endl;
			}
		}
		return *this;
	}
};
class Myvec{//�Լ������������
public:
	vector<const Volume*> m_array;//�����ŵ����ָ���vector����                  ��������ָ��
	int m_rong = 0;//�����������

	Myvec() = default;//Ĭ�Ϲ��캯��
	Myvec(int n) : m_rong(n) {}//�вι��캯��
	Myvec(const Myvec& c) : m_array(c.m_array),m_rong(c.m_rong) {}//���ƹ��캯��
	~Myvec() = default;//��������

	int size() {
		return m_array.size();
	}
	void addthing(const Volume& p) {//��ӵ����������  �����壬Բ����Բ׶�ࣨ������Ʒ��������ӣ�
		m_array.push_back(&p);//��p�ĵ�ַ�⿪��vector�����ڵĻ���ָ��
	}

	void tosort() {//��������Ԫ�ذ������С��������
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
	void valuesort(vector<const Volume*>& array) {//��������Ԫ�ذ�  ��ֵ�������ı�ֵ   �Ӵ�С����
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

	void toput(Myvec &a) {//����Ÿ�����Ʒ�������ڵ���Ʒ ��Ҫ��Ž���
		valuesort(a.m_array);//����Ÿ�����Ʒ�������� ��ֵ�������ı�ֵ�Ӵ�С����
		int nowv = 0;//����������ڵ�����
		cout << "���ŷ����ǣ�";
		for (int i = 0; i <=a.m_array.size() - 1; ++i) {//ѭ��������������
			if (nowv<(this->m_rong)) {//������Ŀ������������С��������������ɼ�����
				if ((nowv + a.m_array[i]->volume())<= (this->m_rong)){//����������Ʒ���ɲ��ᳬ�������������룬�����1  
					this->addthing(*a.m_array[i]);//��Ŀǰ������Ʒ������������Լ۱ȵķ���Ŀ������
					nowv += a.m_array[i]->volume();//���������Ʒ�������ӵ�Ŀǰ������
					cout << 1;
				}
				else {//�������0
					cout << 0;
				}
			}
			else {//���Ѿ����ˣ�����û���꣬��ʣ�µ����0
				cout << 0;
			}		
		}
	}
};
