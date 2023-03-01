#include <iostream>
using namespace std;


const int n = 5; 

struct LinkedListNode
{
	int size; 
	int CurElementCount;
	int* mass; 
	LinkedListNode* next; 
	LinkedListNode* prev; 
};

struct LinkedList
{
	LinkedListNode* first; 
	LinkedListNode* last; 
};

// �������� ������ ������� ������
void linker_list_add_node(LinkedList* ptr)
{
	LinkedListNode* new_node = new LinkedListNode(); 
	new_node->mass = new int[n]; 
	new_node->size = n; 
	new_node->CurElementCount = 0; 
	new_node->next = nullptr; 
	new_node->prev = nullptr;
	ptr->first = new_node; 
	ptr->last = new_node; 
}

// ���������� ����������� �������, ����� ����, ��� ��������� ������������
void linker_list_add_node(LinkedList* ptr, int value)
{
	LinkedListNode* new_node = new LinkedListNode(); 
	new_node->mass = new int[n]; 
	new_node->mass[0] = value; 
	new_node->size = n; 
	new_node->CurElementCount = 1;

	new_node->prev = ptr->last; 
	ptr->last->next = new_node;
	ptr->last = new_node; 
	ptr->last->next = nullptr; 

}

//���������� �������� � ���������
void linker_list_add(LinkedList* ptr, int value)
{
	if (ptr->last->CurElementCount == ptr->last->size) 
		linker_list_add_node(ptr, value); 
	else 
	{
		ptr->last->mass[ptr->last->CurElementCount] = value; 
		ptr->last->CurElementCount++; 
	}
}

//������� �������� �� �������
void linker_list_insert(LinkedList* ptr, int index, int value)
{
	int prev_s = 0; 
	int s = 0; 
	for (LinkedListNode* cur_node = ptr->first;
		cur_node != nullptr; cur_node = cur_node->next) 
	{
		prev_s = s; 
		s += cur_node->CurElementCount; 
		if (s >= index) 
		{
			index -= prev_s; 
			if (cur_node->CurElementCount == cur_node->size) 
			{
				int size = cur_node->size + 1; 
				int* array = new int[size]; 
				for (int i = 0; i < cur_node->size; i++)
				{
					array[i] = cur_node->mass[i];
				}
				cur_node->size++; 
				delete[] cur_node->mass; 
				cur_node->mass = array;
			}
			for (unsigned int i = cur_node->CurElementCount; i > index; i--)
			{
				cur_node->mass[i] = cur_node->mass[i - 1]; 
			}
			cur_node->mass[index] = value; 
			cur_node->CurElementCount++; 

			return; 
		}
	}
}

//��������� �������� �� �������
void linker_list_delete(LinkedList* ptr, int index)
{
	int prev_s = 0; 
	int s = 0; 
	for (LinkedListNode* cur_node = ptr->first; 
		cur_node != nullptr; cur_node = cur_node->next)
	{
		prev_s = s;
		s += cur_node->CurElementCount; 
		if (s >= index) 
		{
			index -= prev_s; 
			if (cur_node->CurElementCount == 1) 
			{
				if (cur_node->next == nullptr) 
				{
					cur_node->prev->next = nullptr; 
					ptr->last = cur_node->prev; 
					delete[] cur_node->mass; 
					delete cur_node;
				}
				else if (cur_node->prev == nullptr) 
				{
					cur_node->next->prev = nullptr; 
					ptr->first = cur_node->next; 
					delete[] cur_node->mass; 
					delete cur_node; 
				}
				else
				{
					cur_node->prev->next = cur_node->next; 
					cur_node->next->prev = cur_node->prev; 
					delete[] cur_node->mass; 
					delete cur_node; 
				} 
			}
			else 
			{
				for (int i = index; i < cur_node->CurElementCount; i++)
				{
					cur_node->mass[i] = cur_node->mass[i + 1]; 
				}
				cur_node->CurElementCount--; 
			}
			return; 
		}
	}
}

int linked_list_get(LinkedList* ptr, LinkedListNode* out, int index)
{
	int counter = -1;
	for (LinkedListNode* cur_node = ptr->first;
		cur_node != nullptr; cur_node = cur_node->next)
	{
		for (int i = 0; i < cur_node->CurElementCount; i++) {
			counter++;
			if (counter == index)
			{
				*out = *cur_node;
				cout << "������� �� ������� " << index << " = " << cur_node->mass[i] << endl;
				return cur_node->mass[i];
			}
		}
	}
	cout << "��� �������� �� " << index << " �������";
}

// ����� ��������� ������������ �� �����
void linker_list_show(LinkedList* ptr)
{
	for (LinkedListNode* cur_node = ptr->first; 
		cur_node != nullptr; cur_node = cur_node->next) 
	{
		for (int i = 0; i < cur_node->CurElementCount; i++) 
			cout << cur_node->mass[i] << endl;
	}
}

// �������� ��������� �� ���������� ������
void linker_list_delete(LinkedList* ptr)
{
	for (LinkedListNode* cur_node = ptr->first;
		cur_node->next != nullptr; cur_node = cur_node->next)
		delete[] cur_node->mass; 
	delete ptr; 
}


int main()
{
	int value, index = 2;
	LinkedListNode* out = new LinkedListNode();
	LinkedList* ptr = new LinkedList(); // �������� ������ ��� ���������� ������
	ptr->first = nullptr; // ����� ������ ������� � ��������� �� ����������
	ptr->last = nullptr;
	linker_list_add_node(ptr); // ������ ������ ������
	for (int i = 0; i < 30; i++)
	{
		linker_list_add(ptr, i * i); // ��������� ���������� ����������
	}
	 
	linker_list_insert(ptr, 2, 100); // ������� �������� �� �������

	linker_list_delete(ptr, 28); // ��������� �������� � �������

	value = linked_list_get(ptr, out, index);

	linker_list_show(ptr); // ��������� �� ������� �������� �������

	linker_list_delete(ptr); // �������� ����������� ������ �� ������ ����������

	return 0;
}