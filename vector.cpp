#pragma once
#include <vector>

//����һ��vector
std::vector< int > v(10, 0); //������һ��vector�� ��ʼ����Ϊ10 ,ÿ��Ԫ��Ϊ0 ���캯��ʡ��ʱvector�ĳ���Ϊ0
// std::vector< typeName > objectName(length, init);

int main() {

	v.clear(); //���vector
	// objectName.clear()

	v.resize(15, 0); //��vector��ĳ��ȵ���Ϊ15 ��������Ϊ0

	v.pop_back(); //����vectorĩβ��Ԫ��
	
	v.push_back(5);// ��vector��ĩβ����Ԫ��5
	// objectName.push_back(object)

	std::vector< int >::iterator it; //����һ��vector< int >������ ָ��һ��vector�е�һ��int 
	// sstd::vector< typeName >::iterator it;
	//����������ʹ��*it ȡ����ͷ��ֵ 

	v.begin(); //����vector���׸�Ԫ�صĵ�����

	v.end();//����vector��ĩβԪ�صĺ�һλ�ĵ�����

	it = v.begin();
	//erse��Ա����
	//�÷�1
	v.erase(it); //ɾ��vector it��������ָ���Ԫ��
	//�÷�2
	v.erase(v.begin(), v.end()); //ɾ��vector begin��end-1 λ��Ԫ��

	v.insert(v.begin(), 1); //��vector�ĵ����������Ԫ�������һλ ��v.begin()��ֵ����Ϊ1
	
}