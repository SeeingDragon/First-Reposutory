#include<iostream>
#include<string>
using namespace std;
#include <fstream>
#define  FILENAME "empFile.txt"

class Worker {//员工抽象类
public:
    int id;//员工编号
    string name;//员工姓名
    string post;//员工岗位
    string responbility;//员工职责
    Worker(int id = 0, string = "员工姓名", string post = "岗位", string responbility = "职责") {
        this->id = id;
        this->name = name;
        this->post = post;
        this->responbility = responbility;
    }
    virtual void showinfo() {
        cout << "员工编号：" << this->id << endl;
        cout << "员工姓名：" << this->name << endl;
        cout << "岗位：" << this->post << endl;
        cout << "岗位职责：" << this->responbility << endl;
    };
    virtual string getpost() {
        return string("岗位");
    };
    virtual ~Worker() {//析构函数要定义，因为原来如果基类里有虚函数，定义了基类指针指向派生类，就会需要定义基类虚析构，这样，基类指针析构的时候，就会先析构派生类，再析构基类。
        cout << "这是析构函数" << endl;
    }
};


class WorkerManager :public Worker {
public:
    int number;
    Worker** array;
    bool FileIsEmpty;
    //构造函数
    WorkerManager() {
        //cout<<"这是构造函数"<<endl;
        this->number = 0;
        this->array = NULL;
    };
    void showmenu();
    void add_worker();
    void show_allinfo();
    void deletworker();
    void replace_info();
    void find_info();
    void sortworker();
    void save();
    ~WorkerManager() {
        //cout<<"这是析构函数"<<endl;
        if (this->array != NULL) {
            delete[] this->array;
        }
    };
};



class commonstaff :public Worker {
public:
    commonstaff(int id, string name) {
        this->id = id;
        this->name = name;
        this->post = "普通员工";
        this->responbility = "完成经理交给的任务";
    }
    void showinfo() {
        cout << "员工编号：" << this->id << endl;
        cout << "员工姓名：" << this->name << endl;
        cout << "岗位：普通员工" << endl;
        cout << "岗位职责：完成经理交给的任务" << endl;
    }
    string getpost() {
        return string("员工");
    }

};

class management :public Worker {
public:
    management(int id, string name) {
        this->id = id;
        this->name = name;
        this->post = "经理";
        this->responbility = "完成老板交给的任务，并下发任务给员工";
    }
    void showinof() {
        cout << "员工编号：" << this->id << endl;
        cout << "员工姓名：" << this->name << endl;
        cout << "岗位：经理" << endl;
        cout << "岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
    }
    string getpost() {
        return string("经理");
    }
};
class boss :public Worker {
public:
    boss(int id, string name) {
        this->id = id;
        this->name = name;
        this->post = "老板";
        this->responbility = "管理公司所有事务";
    }
    void showinof() {
        cout << "员工编号：" << this->id << endl;
        cout << "员工姓名：" << this->name << endl;
        cout << "岗位：老板" << endl;
        cout << "岗位职责：管理公司所有事务" << endl;
    }
    string getpost() {
        return string("老板");
    }
};

void WorkerManager::showmenu() {
    cout << "0.退出当前系统" << endl;
    cout << "1.增加职工信息" << endl;
    cout << "2.显示职工信息" << endl;
    cout << "3.删除职工信息" << endl;
    cout << "4.修改职工信息" << endl;
    cout << "5.查找职工信息" << endl;
    cout << "6.按照编号排序" << endl;
    cout << "7.清空所有文档" << endl;
}

void WorkerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < this->number; i++) {
        ofs << this->array[i]->id << " "
            << this->array[i]->name << " "
            << endl;
    }
    ofs.close();
}


void WorkerManager::add_worker() {
    cout << "请输入增加的职工数量" << endl;
    int addnum = 0;
    cin >> addnum;
    if (addnum > 0) {
        //计算新空间大小
        int newsize = this->number + addnum;
        //开辟新空间
        Worker** newspcae = new Worker * [newsize];//???

        //将原空间放到新空间下
        if (this->array != NULL)
        {
            for (int i = 0; i < this->number; i++) {
                newspcae[i] = this->array[i];
            }
        }
        //输入新数据
        for (int i = 0; i < addnum; i++) {
            int id;
            string name;
            int dselect;
            cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
            cin >> id;
            cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
            cin >> name;

            cout << "请选择该职工的岗位:" << endl;
            cout << "1.普通职工 2.经理 3.老板 " << endl;
            cin >> dselect;

            Worker* worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new commonstaff(id, name);
                break;
            case 2:
                worker = new management(id, name);
                break;
            case 3:
                worker = new boss(id, name);
                break;
            default:
                cout << "输入错误" << endl;
                break;
            }
            newspcae[this->number + i] = worker;
        }
        //释放原有空间
        delete[] this->array;
        //更新新空间的指向
        this->array = newspcae;
        //更新新的个数
        this->number = newsize;
        //提示信息
        cout << "成功添加" << addnum << "名新职工" << endl;
        //cout<<this->number<<endl;
        this->save();
    }
    else {
        cout << "输入错误" << endl;
    }
    //system("pause");
    //system("cls");
}
void WorkerManager::show_allinfo() {
    if (this->array != NULL)
    {
        for (int i = 0; i < this->number; i++)
        {
            array[i]->showinfo();
        }
    }
    else cout << "没有任何职工" << endl;
}
//删除职工
void WorkerManager::deletworker()
{
    cout << "请输入要删除的职工的编号" << endl;
    int n = 0;
    cin >> n;
    if (this->array != NULL)
    {
        for (int i = 0; i < this->number; i++)
        {
            if (array[i]->id == n)
            {
                for (int j = i; j < this->number - 1; j++)
                {
                    array[i] = array[i + 1];
                }
                this->number--;
                cout << "删除成功" << endl;
            }
        }
    }
    else
    {
        cout << "没有任何员工信息" << endl;
    }

}





//查找编号修改职工信息
void WorkerManager::replace_info() {
    int n = 0;
    cout << "请输入要修改的职工的编号" << endl;
    cin >> n;
    if (this->array != NULL)
    {
        for (int i = 0; i < this->number; i++)
        {
            if (array[i]->id == n)
            {
                cout << "请选择是否要修改姓名" << endl;
                int select = 0;
                cin >> select;
                if (select == 1)
                {
                    cout << "请输入新姓名" << endl;
                    string name;
                    cin >> name;
                    array[i]->name = name;
                }
            }
        }

    }
}

void WorkerManager::find_info() {
    int n = 0;
    cout << "请输入要查找的职工的编号" << endl;
    cin >> n;
    if (this->array != NULL)
    {
        for (int i = 0; i < this->number; i++)
        {
            if (array[i]->id == n)
            {
                this->array[i]->showinfo();
            }
        }
    }
    else
    {
        cout << "当前没有任何员工信息" << endl;
    }
}
//职工排序
void WorkerManager::sortworker()
{
    int m_id = 0;
    string m_name;
    string m_post;
    string m_responbility;
    for (int j = 0; j < this->number - 1; j++)
    {
        for (int i = 0; i < this->number - 1 - j; i++)
        {
            if (this->array[i]->id > this->array[i + 1]->id)
            {
                m_id = array[i]->id;
                m_name = array[i]->name;
                m_post = array[i]->post;
                m_responbility = array[i]->responbility;
                array[i]->id = array[i + 1]->id;
                array[i]->name = array[i + 1]->name;
                array[i]->post = array[i + 1]->post;
                array[i]->responbility = array[i + 1]->responbility;
                array[i + 1]->id = m_id;
                array[i + 1]->name = m_name;
                array[i + 1]->post = m_post;
                array[i + 1]->responbility = m_responbility;
            }
        }
    }
}


int main()
{
    int flag = 1;
    int select = 0;
    WorkerManager wm;
    wm.showmenu();
    while (true)
    {
        if (flag % 5 == 0) wm.showmenu();
        cout << "请输入选择" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
            cout << "系统成功退出" << endl;
            exit(0);
        case 1://添加职工信息
            wm.add_worker();
            flag++;
            break;
        case 2://显示公司所有职工信息
            wm.show_allinfo();
            flag++;
            break;
        case 3://按照编号删除员工信息
            wm.deletworker();
            flag++;
            break;
        case 4://修改员工信息
            wm.replace_info();
            flag++;
            break;
        case 5://查找员工
            wm.find_info();
            flag++;
            break;
        case 6:
            wm.sortworker();
            flag++;
            break;
        case 7:
            flag++;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
    }
    system("pause");
    return 0;


    //多态测试
                // Worker  * worker = NULL;
                // worker = new commonstaff(1, "张三");
                // worker->showinfo();
                // worker=new boss(3,"李四");
                // worker->showinfo();
                // worker=new boss(4,"李五");
                // worker->showinfo();
}