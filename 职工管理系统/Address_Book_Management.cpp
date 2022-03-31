#include<iostream>
#include<string>
using namespace std;
#include <fstream>
#define  FILENAME "empFile.txt"

class Worker {//Ա��������
public:
    int id;//Ա�����
    string name;//Ա������
    string post;//Ա����λ
    string responbility;//Ա��ְ��
    Worker(int id = 0, string = "Ա������", string post = "��λ", string responbility = "ְ��") {
        this->id = id;
        this->name = name;
        this->post = post;
        this->responbility = responbility;
    }
    virtual void showinfo() {
        cout << "Ա����ţ�" << this->id << endl;
        cout << "Ա��������" << this->name << endl;
        cout << "��λ��" << this->post << endl;
        cout << "��λְ��" << this->responbility << endl;
    };
    virtual string getpost() {
        return string("��λ");
    };
    virtual ~Worker() {//��������Ҫ���壬��Ϊԭ��������������麯���������˻���ָ��ָ�������࣬�ͻ���Ҫ�������������������������ָ��������ʱ�򣬾ͻ������������࣬���������ࡣ
        cout << "������������" << endl;
    }
};


class WorkerManager :public Worker {
public:
    int number;
    Worker** array;
    bool FileIsEmpty;
    //���캯��
    WorkerManager() {
        //cout<<"���ǹ��캯��"<<endl;
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
        //cout<<"������������"<<endl;
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
        this->post = "��ͨԱ��";
        this->responbility = "��ɾ�����������";
    }
    void showinfo() {
        cout << "Ա����ţ�" << this->id << endl;
        cout << "Ա��������" << this->name << endl;
        cout << "��λ����ͨԱ��" << endl;
        cout << "��λְ����ɾ�����������" << endl;
    }
    string getpost() {
        return string("Ա��");
    }

};

class management :public Worker {
public:
    management(int id, string name) {
        this->id = id;
        this->name = name;
        this->post = "����";
        this->responbility = "����ϰ彻�������񣬲��·������Ա��";
    }
    void showinof() {
        cout << "Ա����ţ�" << this->id << endl;
        cout << "Ա��������" << this->name << endl;
        cout << "��λ������" << endl;
        cout << "��λְ������ϰ彻�������񣬲��·������Ա��" << endl;
    }
    string getpost() {
        return string("����");
    }
};
class boss :public Worker {
public:
    boss(int id, string name) {
        this->id = id;
        this->name = name;
        this->post = "�ϰ�";
        this->responbility = "����˾��������";
    }
    void showinof() {
        cout << "Ա����ţ�" << this->id << endl;
        cout << "Ա��������" << this->name << endl;
        cout << "��λ���ϰ�" << endl;
        cout << "��λְ�𣺹���˾��������" << endl;
    }
    string getpost() {
        return string("�ϰ�");
    }
};

void WorkerManager::showmenu() {
    cout << "0.�˳���ǰϵͳ" << endl;
    cout << "1.����ְ����Ϣ" << endl;
    cout << "2.��ʾְ����Ϣ" << endl;
    cout << "3.ɾ��ְ����Ϣ" << endl;
    cout << "4.�޸�ְ����Ϣ" << endl;
    cout << "5.����ְ����Ϣ" << endl;
    cout << "6.���ձ������" << endl;
    cout << "7.��������ĵ�" << endl;
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
    cout << "���������ӵ�ְ������" << endl;
    int addnum = 0;
    cin >> addnum;
    if (addnum > 0) {
        //�����¿ռ��С
        int newsize = this->number + addnum;
        //�����¿ռ�
        Worker** newspcae = new Worker * [newsize];//???

        //��ԭ�ռ�ŵ��¿ռ���
        if (this->array != NULL)
        {
            for (int i = 0; i < this->number; i++) {
                newspcae[i] = this->array[i];
            }
        }
        //����������
        for (int i = 0; i < addnum; i++) {
            int id;
            string name;
            int dselect;
            cout << "�������" << i + 1 << "����ְ�����:" << endl;
            cin >> id;
            cout << "�������" << i + 1 << "����ְ������:" << endl;
            cin >> name;

            cout << "��ѡ���ְ���ĸ�λ:" << endl;
            cout << "1.��ְͨ�� 2.���� 3.�ϰ� " << endl;
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
                cout << "�������" << endl;
                break;
            }
            newspcae[this->number + i] = worker;
        }
        //�ͷ�ԭ�пռ�
        delete[] this->array;
        //�����¿ռ��ָ��
        this->array = newspcae;
        //�����µĸ���
        this->number = newsize;
        //��ʾ��Ϣ
        cout << "�ɹ����" << addnum << "����ְ��" << endl;
        //cout<<this->number<<endl;
        this->save();
    }
    else {
        cout << "�������" << endl;
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
    else cout << "û���κ�ְ��" << endl;
}
//ɾ��ְ��
void WorkerManager::deletworker()
{
    cout << "������Ҫɾ����ְ���ı��" << endl;
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
                cout << "ɾ���ɹ�" << endl;
            }
        }
    }
    else
    {
        cout << "û���κ�Ա����Ϣ" << endl;
    }

}





//���ұ���޸�ְ����Ϣ
void WorkerManager::replace_info() {
    int n = 0;
    cout << "������Ҫ�޸ĵ�ְ���ı��" << endl;
    cin >> n;
    if (this->array != NULL)
    {
        for (int i = 0; i < this->number; i++)
        {
            if (array[i]->id == n)
            {
                cout << "��ѡ���Ƿ�Ҫ�޸�����" << endl;
                int select = 0;
                cin >> select;
                if (select == 1)
                {
                    cout << "������������" << endl;
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
    cout << "������Ҫ���ҵ�ְ���ı��" << endl;
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
        cout << "��ǰû���κ�Ա����Ϣ" << endl;
    }
}
//ְ������
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
        cout << "������ѡ��" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
            cout << "ϵͳ�ɹ��˳�" << endl;
            exit(0);
        case 1://���ְ����Ϣ
            wm.add_worker();
            flag++;
            break;
        case 2://��ʾ��˾����ְ����Ϣ
            wm.show_allinfo();
            flag++;
            break;
        case 3://���ձ��ɾ��Ա����Ϣ
            wm.deletworker();
            flag++;
            break;
        case 4://�޸�Ա����Ϣ
            wm.replace_info();
            flag++;
            break;
        case 5://����Ա��
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
            cout << "�����������������" << endl;
            break;
        }
    }
    system("pause");
    return 0;


    //��̬����
                // Worker  * worker = NULL;
                // worker = new commonstaff(1, "����");
                // worker->showinfo();
                // worker=new boss(3,"����");
                // worker->showinfo();
                // worker=new boss(4,"����");
                // worker->showinfo();
}