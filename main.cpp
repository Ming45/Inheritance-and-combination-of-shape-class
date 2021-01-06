#include"Shape.h"

int main() {
	Point p(0, 0), p1(1, 0),p2(2,0),p3(3,0), p4(4, 0), p5(5, 0);
    Line s1(p, p1), s2(p,p2),s3(p,p3), s4(p, p4), s5(p, p5);//分别是长度1，2，3，4，5的
//	Delta d(s1, s2), d2(d);

//	Rect r(s1, s2), r2(r);
    Cub c1(s1, s1, s1,10),c2(s1, s1, s2, 9), c3(s1, s1, s3, 8), c4(s1, s1, s4, 7), c5(s1, s1, s5, 1);
	s1 < s2;

	c1 < c2;

//容器测试
	Point p23(23, 0), p31(31, 0), p29(29, 0), p44(44, 0), p53(53, 0), p38(38, 0), p63(63, 0), p85(85, 0), p89(89, 0), p82(82, 0);

	Line s23(p, p23), s31(p, p31), s29(p, p29), s44(p, p44), s53(p, p53), s38(p, p38), s63(p, p63), s85(p, p85), s89(p, p89), s82(p, p82) ;
	
	Cub w1(s1,s1,s23,92), w2(s1, s1, s31, 57), w3(s1, s1, s29, 49), w4(s1, s1, s44, 68), w5(s1, s1, s53, 60), w6(s1, s1, s38, 43), w7(s1, s1, s63, 67), w8(s1, s1, s85, 84), w9(s1, s1, s89, 87), w10(s1, s1, s82, 72);

	Circle yo(p, 1);//单位圆
	Cylind cy1(yo, 23 / 3.14, 92);//体积23,价值92  的圆柱
	Cone co2(yo, 93 / 3.14, 57);//体积31，价值57  的圆锥
	
	Myvec mm;//给定物品的容器
	mm.addthing(cy1);//圆柱
	mm.addthing(co2);//圆锥
	mm.addthing(w3);
	mm.addthing(w4);
	mm.addthing(w5);
	mm.addthing(w6);
	mm.addthing(w7);
	mm.addthing(w8);
	mm.addthing(w9);
	mm.addthing(w10);

	cout << "对其按体积从小到大排序：" << endl;
	mm.tosort(); 
	for (int i = 0; i <= mm.size() - 1; ++i) {
		cout << mm.m_array[i]->volume() <<"  "<< mm.m_array[i]->getvalue() <<"  "<< mm.m_array[i]->getvalue()/mm.m_array[i]->volume() << endl;;
	}

	Myvec dd(165);//最大容量为165的目标容器
	dd.toput(mm);

	return 0;
}