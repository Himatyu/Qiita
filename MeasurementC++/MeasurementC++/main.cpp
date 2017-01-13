#include<fstream>
#include<typeindex>
#include<string>
#include"NullType.h"
#include"TypeList.h"

#include<list>
#include<vector>
#include<array>
#include<deque>
#include<forward_list>
#include<map>
#include<unordered_map>
#include<unordered_set>

#include<memory>
#include<functional>
#include<chrono>
#include<thread>
#include<mutex>

using namespace std;
using namespace Utility;

fstream fs;
template<typename T >
void OutputSize()
{
	type_index type = typeid(T::Head);
	fs << string(
		type.name()) +
		string(" ")+
		to_string(sizeof(T::Head))<< endl;
	OutputSize<T::Tail>();
}

template<>
void OutputSize<NullType>()
{
	fs << endl;
	return;
}

void Predefined()
{
	//�f�[�^�^�͈̔�(https://msdn.microsoft.com/ja-jp/library/s3f49ktz.aspx)�����Ă��邯�ǈꉞ
	OutputSize<
		TypeList10<
		int,
		unsigned,
		char,
		unsigned char,
		short,
		unsigned short,
		long long,
		bool,
		float,
		double
		>> ();

	OutputSize<
		TypeList10<
		int&,
		unsigned&,
		char&,
		unsigned char&,
		short&,
		unsigned short&,
		long long&,
		bool&,
		float&,
		double&
		>> ();

	OutputSize<
		TypeList10<
		int*,
		unsigned*,
		char*,
		unsigned char*,
		short*,
		unsigned short*,
		long long*,
		bool*,
		float*,
		double*
		>> ();
}

void Contaier()
{
	//�R���e�i

	OutputSize<
		TypeList8<
		list<int>,					//_Container_proxy*:4 Node*:4 size_t:4 �^�ˑ��Ȃ�
		vector<int>,				//_Container_proxy*:4 first*:4 last*:4 end*:4 �^�ˑ��Ȃ�
		deque<double>,				//_Container_proxy*:4 Map*:4 size:4 off:4 size:4 �^�ˑ��Ȃ�
		forward_list<double>,		//_Container_proxy*:4 head* 4 �^�ˑ��Ȃ�
		map<string, int>,			//_Container_proxy*:4 head*:4 size:4
		unordered_map<string, int >,//list:12 vector:16 Mask:4 Maxidx:4 _Mypair:4
		unordered_set<int>,			//list:12 vector:16 Mask:4 Maxidx:4 _Mypair:4
		array<int, 8>
		>> ();

}

void Other()
{
	OutputSize<TypeList7<
		string,
		shared_ptr<int>,
		function<void(void)>,
		chrono::system_clock,
		thread,
		mutex,
		type_index
		>>();

}

class a 
{
	a* next;
};
class b
{
	bool l;
	bool s;
	b* next;
};
class c
{
	bool l;
	c* next;
	bool s;
};
int main()
{
	auto sizea = sizeof(a);
	auto sizeb = sizeof(b);
	auto sizec = sizeof(c);
	fs.open("output.txt",ios::out);

	Predefined();
	Contaier();
	Other();

	fs.close();
}