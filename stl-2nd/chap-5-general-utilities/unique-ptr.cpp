#include <iostream>
#include <string>
#include <memory>
#include <dirent.h>
#include <cstring>
#include <cerrno>


using namespace std;
class DirCloser {
public:
	void operator ()(DIR* dp) {
		if (closedir(dp) != 0) {
			std::cerr << "OOPS: closedir () failed " << std::endl;
		}
	}
};

int main()
{
	{
		unique_ptr<DIR, DirCloser> pDir(opendir("./"));
		struct dirent *dp;
		while ( (dp = readdir(pDir.get())) != nullptr) {
			string filename(dp->d_name);
			cout << "process " << filename << endl;
		}
	}
	{
		cout << "=======================lambda delter ================\n";
		auto l = [] (DIR *dp) { if (closedir(dp) != 0) cerr << "OOPS: closedir() failed" << endl;};
		unique_ptr<DIR, decltype(l)> pDir(opendir("./"),l);
		struct dirent *dp;
		while ( (dp = readdir(pDir.get())) != nullptr) {
			string filename(dp->d_name);
			cout << "process " << filename << endl;
		}
	}

	{
		cout << "=====================more direct ===============\n";
		unique_ptr<DIR, void(*)(DIR*)> pDir(opendir("./"), 
							[] (DIR* dp) { if (closedir(dp) != 0) cerr << "OOPS: closedir() failed" << endl;} );

		struct dirent *dp;
		while ( (dp = readdir(pDir.get())) != nullptr) {
			string filename(dp->d_name);
			cout << "process " << filename << endl;
		}
	}
						
}


