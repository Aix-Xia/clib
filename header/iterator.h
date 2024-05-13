#pragma once
#ifndef _TERATOR_H_
#define _TERATOR_H_

template <typename T>
class Iterator {
public:
	Iterator(T* tptr, int size) {
		ptr = tptr;
		remain = size;
	}
	~Iterator() {

	}
	// ���������Ƿ��и���Ԫ��
	bool IsEnd() {
		return remain == 0;
	}
	// ���ص���������һ��Ԫ�ز����µ�����״̬
	T Next() {
		if (remain <= 0) {
			// ����������ޣ�������
			return -1;
		}
		remain--;
		return *(ptr++);
	}

private:
	T* ptr;
	int remain;
};
/*
sample:
	int numbers[] = { 1, 2, 3, 4, 5 };
	Iterator<int> it(numbers, sizeof(numbers)/sizeof(int));
	while (it.HasNext()) {
		printf("%d ", it.Next());
	}
*/

template<typename T>
bool lam(int index, int count, T* iter, T* item) {
	if (index < count) {
		*item = *(iter + index);
		return true;
	}
	else if (item == NULL) {
		return false;
	}
	else {
		return false;
	}
}
#define LOOP(type, iter, item)		int cnt=sizeof(iter)/sizeof(iter[0]); type item; for(int i = 0; lam(i, cnt, iter, &item); i++)

#endif
