package com.example.application_designer;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;

import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class class_guangzhou_Fragment extends Fragment {
    private int[] icon;
    private String[] news_title;
    private String[] news_source;
    private String[] news_time;
    private ListView mListView;
    private View view;
    @Override//覆盖父类的方法
    public View onCreateView(LayoutInflater inflater, final ViewGroup container, Bundle savedInstanceState){
        view=inflater.inflate(R.layout.news_fragment,container,false);
        final MainActivity activity=(MainActivity) getActivity();
        icon=activity.getIcon();
        news_title=activity.gettitle();
        news_time=activity.gettime();
        news_source=activity.getSource();
        if (view!=null){
            initView();
        }
        mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                class_guangzhou_Fragment_content contentFragment=new class_guangzhou_Fragment_content();
                contentFragment.position=position;//直接传递变量值就行了
                activity.replaceFragment(contentFragment);

            }
        });
        return view;
    }
    private void initView(){
        mListView=(ListView) view.findViewById(R.id.recommendlist);
        if (icon!=null){
            mListView.setAdapter(new MyAdapter());
        }
    }
    class MyAdapter extends BaseAdapter{
        @Override
        public int getCount(){
            return icon.length;
        }
        @Override
        public Object getItem(int position){
            return icon[position];
        }
        @Override
        public long getItemId(int position){
            return position;
        }
        @Override
        public View getView(int position,View convertView,ViewGroup parent){
            convertView=View.inflate(getActivity(),R.layout.item_list,null);
            ImageView mNameTV=(ImageView) convertView.findViewById(R.id.news_icon);
            mNameTV.setBackgroundResource(icon[position]);
            TextView title=(TextView) convertView.findViewById(R.id.news_title);
            title.setText(news_title[position]);
            TextView source=(TextView)convertView.findViewById(R.id.news_source);
            source.setText(news_source[position]);
            TextView time=(TextView)convertView.findViewById(R.id.news_time);
            time.setText(news_time[position]);
            return convertView;
        }
    }
}
