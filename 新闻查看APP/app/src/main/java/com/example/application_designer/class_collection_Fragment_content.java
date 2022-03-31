package com.example.application_designer;
import android.Manifest;
import android.content.ContentValues;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.fragment.app.Fragment;

public class class_collection_Fragment_content extends Fragment {
    private View view;
    public ImageView micon;
    public TextView mcontent;
    public TextView mtitle;
    public TextView tv_comment;
    public Button bt_comment;
    public Button bt_collect;
    public EditText comment_content;
    public TextView mtime;
    public TextView msource;
    private String[] time;
    private String[] source;
    private int[] content;
    private String[] title;
    private int[] icon;
    public int position=1;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.collection_content, container, false);
        if (view!=null){
            initView();
        }
        content=((MainActivity)getActivity()).getContent();
        title=((MainActivity)getActivity()).gettitle();
        icon=((MainActivity)getActivity()).getIcon();
        time=((MainActivity)getActivity()).gettime();
        source=((MainActivity)getActivity()).getSource();
        mcontent.setText(content[position]);
        mtitle.setText(title[position]);
        micon.setBackgroundResource(icon[position]);
        mtime.setText(time[position]);
        msource.setText(source[position]);
        return view;
    }
    public void initView(){
        mcontent=(TextView)view.findViewById(R.id.collection_content_content);
        mtitle=(TextView)view.findViewById(R.id.collection_content_title);
        micon=(ImageView)view.findViewById(R.id.collection_news_icon_content);
        mtime=(TextView)view.findViewById(R.id.collection_content_time);
        msource=(TextView)view.findViewById(R.id.collection_content_source);
        bt_comment=(Button)view.findViewById(R.id.collection_comment);
        bt_collect=(Button)view.findViewById(R.id.collection_collect);
        tv_comment=(TextView)view.findViewById(R.id.collection_tv_comment);
        comment_content=(EditText)view.findViewById(R.id.collection_comment_content);
        bt_comment.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Toast.makeText((MainActivity)getActivity(),"信息已删除",Toast.LENGTH_SHORT).show();
                String c=comment_content.getText().toString();
                tv_comment.setText(c);
            }
        });
        bt_collect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int count=((MainActivity)getActivity()).readcount(((MainActivity)getActivity()).myHelper,"Select count(_id) from collection;");
                //((MainActivity)getActivity()).add("collection",position,((MainActivity)getActivity()).myHelper);
                ((MainActivity)getActivity()).delet("collection","icon=?",icon[position],((MainActivity)getActivity()).myHelper);
                Toast.makeText((MainActivity)getActivity(),"新闻已取消收藏",Toast.LENGTH_SHORT).show();
                for(int i=1;i<=count-position;i++){
                    update(position+i,((MainActivity)getActivity()).myHelper);
                }
            }
        });
    }
    public void setText(String text,TextView textView){
        textView.setText(text);
    }
    public int update(int id, MainActivity.MyHelper myHelper){
        SQLiteDatabase db=myHelper.getWritableDatabase();
        ContentValues values=new ContentValues();
        values.put("_id",id-1);
        int number=db.update("collection",values,"_id=?",new String[]{id+""});
        db.close();
        return number;
    }
}
