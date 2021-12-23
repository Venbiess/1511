#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
void point(string error)
{
  string s="1";
  while (s!=".")
    {
      cout << error << "\n\nPRESS '.' TO CONTINUE.\n";
      cin >> s;
      system("clear");
    }
}
bool isNumber(const string& s)
{
    for (char const &ch : s) {
        if (isdigit(ch) == 0) 
            return false;
    }
    return true;
 }
class table
{

    private:
        string name;
        vector <string> columns_name={};
        vector <vector <string>> table;
    public:
        void load_from_file(string file)
        {
          ifstream input(file);
          string line="", temp=""; int count=0;
          getline(input, line);
          name=line;
          getline(input, line);
          if (line=="") table.push_back({});// exit(0);
          columns_name = {};
          vector <string> vec_temp;
          for (int i=0; i<line.size();i++)
          {
            if (line[i]=='#'){if (temp!="") columns_name.push_back(temp); temp="";}
            else temp+=line[i];
          }
          while (getline(input,line))
          {
            vec_temp = {};
            for (int i=0; i<line.size();i++)
            {
              if (line[i]=='#'){if (temp!="") vec_temp.push_back(temp);temp="";}
              else temp+=line[i];
            }
            table.push_back(vec_temp);
          }
          
        }
        vector <string> tabcol()
        {
            return columns_name;
        }
        string get_name()
        {
          return name;
        }
        double countavm(int pid, int sid)
        {
          int count=0, sum=0;
          for (int i=0; i<table.size(); i++)
          {
            if (stoi(table[i][2])==sid and stoi(table[i][1])==pid)
            {
              sum+=stoi(table[i][3]);
              count++;
            }
          }
          if (count==0)
          {
            cout << "There is no any marks";
            return 0;
          }
          else return double(sum)/double(count);
        }
        void add()
        {
                vector <string> information = {}; string s;
                for (int i=1; i<columns_name.size(); i++)
                {
                    cout << "Enter pupil's " << columns_name[i] << ": ";
                    cin >> s;
                    if (columns_name[i]=="AGE" or columns_name[i]=="CLASS" or columns_name[i]=="subject_id" or columns_name[i]=="mark_id" or columns_name[i]=="mark" or columns_name[i]=="id") 
                    {
                      while (!isNumber(s) or (columns_name[i]=="mark" & (stoi(s)>5 or stoi(s)<1) or (columns_name[i]=="CLASS" and (stoi(s)>11 or stoi(s)<1))))
                      {
                        cout << "Please, enter a correct number.\n";
                        cin >> s;
                      }

                    }
                    information.push_back(s);
                }

            string id="0";
            if (table.size()>0) id = to_string(stoi(table[table.size()-1][0])+1);
            information.insert(information.begin(), id);
            table.push_back(information);
        }
        void recount()
        {
          for (int i=0; i<table.size(); i++) table[i][0]=to_string(i);
        }
        void delet(int num)
        {
            table.erase (table.begin()+num ,table.begin()+num+1);
            for (int i=0; i<table.size(); i++)
            {
                table[i][0]=to_string(i);
            }
        }
        void show()
        {
            for (int i=0; i<columns_name.size();i++)
            {
                cout << columns_name[i] << "\t";
            }
            cout << endl;
            for (int i=0; i<table.size(); i++)
            {
                for (int j=0; j<table[i].size(); j++)
                    cout << table[i][j] << '\t';
                cout << endl;
            }
            cout <<endl<<endl;
            point("");
        }
        void save_file()
        {
          ofstream output(name);
          string text=name+"\n#";
          for (int i=0; i<columns_name.size(); i++)
            text+=columns_name[i]+"#";
          text+="\n";
          for (int i=0; i<table.size(); i++)
          {
            text+="#";
            for (int j=0; j<columns_name.size(); j++)
            {
              text+=table[i][j]+"#";
            }
            text+="\n";
          }
          output << text;
        }
        void show_stolb(string value)
        {
            int k=-1;
            for (int i=0; i<columns_name.size(); i++)
            {
                if (columns_name[i]==value) {k=i; break;}
            }
            if (k!=-1)
            {
              for (int j=0; j<table.size(); j++) 
                cout << table[j][k] << endl;
              point("");
            }
            else point("There is no such column.");
        }
        int size()
        {
          return table.size();
        }
        void add_stolb(string name)
        {
            columns_name.push_back(name);
            for (int i=0; i<table.size(); i++)
            {
                table[i].push_back("NULL");
            }
        }
        void delet_stolb(string value)
        {
            int k=-1;
            for (int i=0; i<columns_name.size(); i++)
            {
                if (value==columns_name[i]) {k=i; break;}
            }
            if (k>0)
            {
              columns_name.erase (columns_name.begin()+k,columns_name.begin()+k+1);
              for (int i=0; i<table.size(); i++)
              {
                table[i].erase(table[i].begin()+k, table[i].begin()+k+1);
              }
            }
            else 
            {
              if (k==0) point("Permission denied.");
              if (k==-1) point("There is no such column.");
            }
        }
        void edit(int idi, string column, string value)
        {
            int k=-1;
            for (int i=0; i<columns_name.size(); i++)
            {
                if (column==columns_name[i]) {k=i; break;}
            }
            table[idi][k]=value;
        }
        bool check(int i, int delid, int num)
        {
          //i - stroka; delid - deleted id
            if (stoi(table[i][num])==delid)
            {
              table.erase(table.begin()+i, table.begin()+i+1);
              return true;
            }
            if (stoi(table[i][num])>delid)
            {
              table[i][num]=to_string(stoi(table[i][num])-1);
            }
            return false;
        }
        

};
class baza
{
    private:
      vector <table> baza;
      vector <string> list;
      table t={};

    public:
      vector <string> p_names()
      {
        return list;
      }
      void create_table(string name)
        {
            name+=".txt";
            ofstream file(name);
            file << name;
            baza.push_back(t);
            list.push_back(name);
        }
      void delete_table(string name)
        {
          remove((name + ".txt").c_str());
        }
      int table_num(string name)
      {
        for (int i=0; i<list.size(); i++)
        {
          if (list[i]==name) return i;
        }
        return -1;
      }
      double avm(int pid, int sid)
      {
        table tab; tab.load_from_file("Marks.txt");
        return tab.countavm(pid,sid);
      }
      table delete_from_table(int table_id, int id)
      {
        table tab; tab.load_from_file("Marks.txt"); int num;
        if (list[table_id]=="Pupils.txt" or list[table_id]=="Subjects.txt")
        {
          if (list[table_id]=="Pupils.txt") num=1;
          else num=2;
          baza[table_id].delet(id);
          int n=tab.size(), count=n;
          for (int i=0; i<tab.size(); i++)
          {
            if (tab.check(i,id, num)) i--;
          }
          tab.recount();
          tab.save_file();
          baza[table_num("Marks.txt")]=tab;
        }
        else
        {
          tab.delet(id);
          tab.recount();
        }
        return baza[table_id];
      }

      void upload_table(string name)
        {
            t={};
            name+=".txt";
            t.load_from_file(name);
            baza.push_back(t);
            list.push_back(name);
        }
      vector <table> get_table()
      {
        return baza;
      }


      
        
};
int main()
{
    table tab; string s,ss; baza bd;
    vector <string> chelovek1,chelovek;
    int action; string saction;
    vector <vector <string>> actions =
    {
        {"1) Create table", "2) Delete table", "3) Edit table", "4) Upload Table"},
        {"1) Add note", "2) Delete note", "3) Go back", "4) Show table", "5) Show Column", "6) Add column","7) Delete Column", "8) Save table", "9) Average Mark"},
    };

    int now=0; vector <string> information;
    while (true)
    {
        cout << setfill('@') << setw(70) << "";
        for (int i=0; i<actions[now].size(); i++)
        {
            if (i%3==0)
            {
                cout << "\n@---. ";
            }
            if (i%3>0) cout << " .---. ";
            cout << actions[now][i];
            if (i%3==2)
            {
                cout << ".---@";
            }
        }
        cout << endl << setfill('@') << setw(70) << "" << endl;
        saction="a";
        cin >> saction;
        while (!isNumber(saction))
        {
          cout << "Please, enter a number \n"; 
          cin >> saction;
        }
        action = stoi(saction);
        if (now==0)
        {
            if (action==1)
            {
                cout << "Enter name of table: ";
                cin >> s;
                bd.create_table(s);
            }
            if (action==2) 
            {
              cout << "Enter name of table: ";
              cin >> s;
              bd.delete_table(s);
            }
            if (action==3)
            {
                vector <string> list = bd.p_names();
                system("clear");
                if (list.size()>0)
                {
                  cout << "Which one would you like to work with?\n";
                  for (int i=0; i<list.size(); i++) cout << i+1 << ") " << list[i] << endl;
                  cin >> s;
                  while (!isNumber(s) or stoi(s)-1<0 or stoi(s)-1>=bd.p_names().size())
                  {
                    cout << "Incorrect number. Try again.\n";
                    cin >> s;
                  }
                  cout << "go";
                  tab=bd.get_table()[stoi(s)-1];
                  now=1;
                }
                else point("There is no any loaded tables. Load tables and try again.");
            }
            if (action==4)
            {
              cout << "Enter name of table: ";
              cin >> s;
              bd.upload_table(s);
              
            }
        }
        else if (now==1)
        {
            if (action==1)
            {
              tab.add();
            }
            if (action==4)
            {
                tab.show();
            }
            if (action==3)
            {
                tab.save_file();
                now=0;
            }
            if (action==2)
            {
                cout << "Enter pupil's id: "; cin >> s;
                tab = bd.delete_from_table(bd.table_num(tab.get_name()),stoi(s));
            }
            if (action==5)
            {
              cout << "Enter name of column: ";
              cin >> s;
              tab.show_stolb(s);    
            }
            if (action==6)
            {
              cout << "Enter name of column: ";
              cin >> s;
              tab.add_stolb(s);
            }
            if (action==7)
            {
              cout << "Enter name of column: ";
              cin >> s;
              tab.delet_stolb(s);
            }
            if (action==8)
            {
              tab.save_file();
              point("The table has been saved succesfuly!:)");
            }
            if (action==9)
            {
              cout << "Enter pupil's id: ";
              cin >> s;
              cout << "Enter id of subject: ";
              cin >> ss;
              cout << "Average mark: " << bd.avm(stoi(s),stoi(ss));
              point("");

            }
        }
        system("clear");
    }
}
