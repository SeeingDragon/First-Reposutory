package com.example.application_designer;


import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends AppCompatActivity {
    //@SuppressLint("NewApi")
    public int maoding=38;
    MyHelper myHelper;
    private Button bt_publish;
    private Button bt_recommend;
    private Button bt_hotbot;
    private Button bt_guangzhou;
    private Button bt_anti_epidemic;
    private Button bt_sport;
    private Button bt_collection;
    SQLiteDatabase db;
    ContentValues values;
    //数据
    private int[] icon_recommend={};
    private int[] icon={R.drawable.recommend_1,R.drawable.recommend_2,R.drawable.recommend_3,R.drawable.recommend_4,R.drawable.recommend_5};
    private String[] new_title={"习近平：教训深刻","让开放的大门越开越大","“团结”表象下 七国集团“面和心不齐”","天问一号交出完美答卷 火星取样木星探测提上日程","“中国与七个小矮人”：德国媒体发文分析七国集团峰会"};
    private String[] time={"2021-06-14 13:34","2021-06-14 06:30","2021-06-14 15:22","2021-06-14 12:44","2021-06-13 16:56"};
    private String[] source={"学习大军","人民网","中国网","人民网","张学昆"};
    private int[] content={R.string.hotbot_1,R.string.hotbot_2,R.string.hotbot_3,R.string.hotbot_4,R.string.hotbot_5};
    public int[] getIcon(){
        return icon;
    }
    public String[] gettitle(){
        return new_title;
    }
    public String[] gettime(){
        return time;
    }
    public String[] getSource(){
        return source;
    }
    public int[] getContent(){
        return content;
    }
    //private String[] time={"2021.5.18","2021.5.18","2021.5.18","2021.5.18","2021.5.18"};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //收藏评论功能
//        tv_comment=(TextView) LayoutInflater.from(MainActivity.this).inflate(R.layout.news_fragment_content,null).findViewById(R.id.comment);
//        bt_comment=(Button)LayoutInflater.from(MainActivity.this).inflate(R.layout.news_fragment_content,null).findViewById(R.id.comment);
//        bt_collect=(Button)LayoutInflater.from(MainActivity.this).inflate(R.layout.news_fragment_content,null).findViewById(R.id.collect);
        //初始化SQL数据库
        myHelper=new MyHelper(MainActivity.this);
        //Fragment调用
        bt_publish=(Button)findViewById(R.id.publish);
        bt_recommend=(Button)findViewById(R.id.bt_recommend);
        bt_hotbot=(Button)findViewById(R.id.bt_hotbot);
        bt_guangzhou=(Button)findViewById(R.id.bt_guangzhou);
        bt_anti_epidemic=(Button)findViewById(R.id.bt_anti_epidemic);
        bt_sport=(Button)findViewById(R.id.bt_sport);
        bt_collection=(Button)findViewById(R.id.collection);
        readdata(5,myHelper,"recommend");
        replaceFragment(new class_recommend_Fragment());
        bt_publish.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
               //for (int i=2;i<=3;i++){
                   //delet("collection","_id=?",23,myHelper);
                    //update(5,3,myHelper);
                   //}
//                String s="0";
//                int count=readcount(myHelper);
//                s=String.valueOf(count);
//                Toast.makeText(MainActivity.this,s,Toast.LENGTH_SHORT).show();
            }
        });
        bt_recommend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=readcount(myHelper,"Select count(_id) from recommend;");
                clear(count);
               readdata(count,myHelper,"recommend");
                replaceFragment(new class_recommend_Fragment());
            }
        });
        bt_hotbot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=readcount(myHelper,"Select count(_id) from hotbot;");
                clear(count);
                readdata(count,myHelper,"hotbot");
                replaceFragment(new class_hotbot_Fragment());
            }
        });
        bt_guangzhou.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=readcount(myHelper,"Select count(_id) from guangzhou;");
                clear(count);
                readdata(count,myHelper,"guangzhou");
                replaceFragment(new class_guangzhou_Fragment());
            }
        });
        bt_anti_epidemic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=readcount(myHelper,"Select count(_id) from anti_epidemic;");
                clear(count);
                readdata(count,myHelper,"anti_epidemic");
                replaceFragment(new class_anti_epidemic_Fragment());
            }
        });
        bt_sport.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=readcount(myHelper,"Select count(_id) from sport;");
                clear(count);
                readdata(count,myHelper,"sport");
                replaceFragment(new class_sport_Fragment());
            }
        });
        bt_collection.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=readcount(myHelper,"Select count(_id) from collection;");
                clear(count);
                readdata(count,myHelper,"collection");
                replaceFragment(new class_collection_Fragment());
            }
        });
    }
    //清空数据函数
    public void clear(int count){
        icon=new int[count];
        new_title=new String[count];
        time=new String[count];
        source=new String[count];
        content=new int[count];
    }
    //动态调用Fragment函数
    public void replaceFragment(Fragment fragment)
    {
        FragmentManager fragmentManager=getSupportFragmentManager();
        FragmentTransaction transaction=fragmentManager.beginTransaction();
        transaction.replace(R.id.fragment,fragment);
        transaction.commit();
    }
    //添加数据
    public void add(String info,int number,MyHelper myHelper){
        //往SQL数据库插入一条数据
      db=myHelper.getWritableDatabase();
      values=new ContentValues();
      values.put("icon",icon[number]);
      values.put("title",new_title[number]);
      values.put("time",time[number]);
      values.put("source",source[number]);
      values.put("content",content[number]);
      db.insert(info,null,values);
      Toast.makeText(MainActivity.this,"信息已添加",Toast.LENGTH_SHORT).show();
      db.close();
    }
    //删除数据库中的数据
    public void delet(String table,String condition,int id,MyHelper myHelper){
        db=myHelper.getWritableDatabase();
        db.delete(table,condition,new String[]{id+""});
        Toast.makeText(MainActivity.this,"信息已删除",Toast.LENGTH_SHORT).show();
        db.close();
    }
    //查看数据有多少行
    public int  readcount(MyHelper myHelper,String table){
        SQLiteDatabase db;
        db=myHelper.getReadableDatabase();
        Cursor cursor1=db.rawQuery(table, null);
        cursor1.moveToFirst();
        int count = cursor1.getInt(0);
        return count;
    }

    //读取数据库中不同的数据
    public void  readdata(int id,MyHelper myHelper,String table){
        SQLiteDatabase db;
        db=myHelper.getReadableDatabase();
//        Cursor cursor1=db.rawQuery(select_SQL, null);
//        cursor1.moveToFirst();
//        int count = cursor1.getInt(0);
        for(int i=1;i<=id;i++){
            Cursor cursor=db.query(table,null,"_id=?",new String[]{i+""},null,null,null);
            if(cursor.getCount()!=0){
                while (cursor.moveToNext()){
                    icon[i-1]=cursor.getInt(cursor.getColumnIndex("icon"));
                    new_title[i-1]=cursor.getString(cursor.getColumnIndex("title"));
                    time[i-1]=cursor.getString(cursor.getColumnIndex("time"));
                    source[i-1]=cursor.getString(cursor.getColumnIndex("source"));
                    content[i-1]=cursor.getInt(cursor.getColumnIndex("content"));
                }
            }
            cursor.close();
        }
        db.close();
        //Toast.makeText(MainActivity.this,"读取成功",Toast.LENGTH_SHORT).show();
    }
// 修改数据
public int update(int id,int count,MyHelper myHelper){
        SQLiteDatabase db=myHelper.getWritableDatabase();
        ContentValues values=new ContentValues();
        values.put("_id",count+1);
        int number=db.update("collection",values,"_id=?",new String[]{id+""});
        db.close();
        Toast.makeText(MainActivity.this,"信息已修改",Toast.LENGTH_SHORT).show();
        return number;
    }
    class MyHelper extends SQLiteOpenHelper{
        public MyHelper(Context context){
            super (context,"news_save.db",null,2);
        }
        @Override
        public void onCreate(SQLiteDatabase db){
            db.execSQL("CREATE TABLE recommend(_id INTEGER PRIMARY KEY AUTOINCREMENT,icon int,title VARCHAR(20),time VARCHAR(20),source VARCHAR(20),content int)");
            db.execSQL("CREATE TABLE hotbot(_id INTEGER PRIMARY KEY AUTOINCREMENT,icon int,title VARCHAR(20),time VARCHAR(20),source VARCHAR(20),content int)");
            db.execSQL("CREATE TABLE guangzhou(_id INTEGER PRIMARY KEY AUTOINCREMENT,icon int,title VARCHAR(20),time VARCHAR(20),source VARCHAR(20),content int)");
            db.execSQL("CREATE TABLE anti_epidemic(_id INTEGER PRIMARY KEY AUTOINCREMENT,icon int,title VARCHAR(20),time VARCHAR(20),source VARCHAR(20),content int)");
            db.execSQL("CREATE TABLE sport(_id INTEGER PRIMARY KEY AUTOINCREMENT,icon int,title VARCHAR(20),time VARCHAR(20),source VARCHAR(20),content int)");
        }
        @Override
        public void onUpgrade(SQLiteDatabase db,int oldVersion,int newVersion){
            //db.execSQL("CREATE TABLE collection(_id INTEGER PRIMARY KEY AUTOINCREMENT,icon int,title VARCHAR(20),time VARCHAR(20),source VARCHAR(20),content int)");
        }
    }
}
