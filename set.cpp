#pragma once
#include <set>

// ��������
// std::set< typeName > objectName;
std::set<int> s;

// ��غ���
int main() {
	//�ڼ���s�����Ԫ��
	//����ԭ�� 
	// pair<iterator, bool> insert(value_type&& _Val)
	//����ֵ���first��Ա�ǲ���󱻲���Ԫ�صĵ�����,second��ԱΪ�Ƿ����ɹ�
	s.insert(int(0));

	//��ѯ������Ԫ�ص�����
	//����ԭ��
	//_NODISCARD size_type size() const noexcept
	s.size();
}