#include <fstream>
#include <iostream>
#include <vector>
#include<algorithm>
#include "page.h"


using namespace std;
vector<Page> idpage;
vector<Page> idpage_for_print;
vector<int> order;
vector<int> idxvector;


class Board {
public:
    Board(int num_jobs, int width, int height, ofstream& output_stream);
    ~Board();

    void print_board();
    void print_job(int job_idx, char job_type, int id);
    void delete_pages(int idx);
    //job functions
    void insert_page(int x, int y, int width, int height, int id, char content, int job_index);
    void delete_page(int id, int job_index);
    void modify_content(int id, char content);
    void modify_position(int id, int x, int y);
    friend class page;

private:
    int num_jobs, width, height;
    ofstream& output;
    char* board;
};


Board::Board(int num_jobs, int width, int height, ofstream& output_stream) : output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width * height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h * width + w] = ' ';
        }
    }
}

Board::~Board() {
    delete board;

}


void Board::print_board() {
    int h, w;
    for (w = 0; w < width + 2; w++) output << "- ";
    output << endl;

    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h * width + w] << " ";
        }
        output << "| " << endl;
    }
    for (w = 0; w < width + 2; w++) output << "- ";
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx << ") ";
    switch (job_type) {

    case 'i':
        output << "Insert ";
        break;
    case 'd':
        output << "Delete ";
        break;
    case 'm':
        output << "Modify ";
        break;
    }

    output << id << endl;
}


void Board::insert_page(int x, int y, int page_width, int page_height, int id, char content, int job_index)//insert_page(0,1,10,15,c)
{
    Page pg(x, y, page_width, page_height, id, content);
    idpage.push_back(pg);
    idpage_for_print.push_back(pg);
    for (int i = 0; i < job_index; i++)
    {
        for (int h = idpage[i].get_Page_y(); h < idpage[i].get_Page_y() + idpage[i].get_Page_height(); h++) {
            for (int w = idpage[i].get_Page_x(); w < idpage[i].get_Page_x() + idpage[i].get_Page_width(); w++) {
                board[h * width + w] = idpage[i].get_Page_content();
            }
        }
    }
    print_board();
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h * width + w] = ' ';
        }
    }
}


void Board::delete_pages(int idx)
{

    if (idpage.size() == 0)
        return;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h * width + w] = ' ';
        }
    }

    int _x = idpage[idx].get_Page_x();
    int _y = idpage[idx].get_Page_y();
    int _width = idpage[idx].get_Page_width();
    int _height = idpage[idx].get_Page_height();

    int idx2 = 0;
    int min_id = 999999;
    bool flag = true;
    while (flag) 
    {
        min_id = 999999;
        flag = false;
        for (int i = idpage.size() - 1; i > idx; i--)
            if (((_x <= idpage[i].get_Page_x()  && idpage[i].get_Page_x() <= _x + _width)
                && (_y <= idpage[i].get_Page_y()  && idpage[i].get_Page_y() <= _y + _height)) ||
                (idpage[i].get_Page_x() <= _x && _x <= idpage[i].get_Page_x() + idpage[i].get_Page_width())
                && ( idpage[i].get_Page_y() <= _y && _y <= idpage[i].get_Page_y() + idpage[i].get_Page_height())) //°ãÄ¥ ¶§
            {
                auto it = find(idxvector.begin(), idxvector.end(), i);
                if (it != idxvector.end())
                    continue;
                if (min_id > idpage[i].get_Page_id()) 
                {
                    idx2 = i;
                    min_id = idpage[i].get_Page_id();
                    flag = true;
                }
            }
        if (flag) 
        {
            delete_pages(idx2);
            idxvector.push_back(idx2);
            order.push_back(idx2);
        }
    }


    for (int i = 0; i < idpage.size(); i++)
    {
        auto it = find(idxvector.begin(), idxvector.end(), i); 
        
        if (it != idxvector.end())
            continue;

        for (int h = idpage[i].get_Page_y(); h < idpage[i].get_Page_y() + idpage[i].get_Page_height(); h++) {
            for (int w = idpage[i].get_Page_x(); w < idpage[i].get_Page_x() + idpage[i].get_Page_width(); w++) {
                board[h * width + w] = idpage[i].get_Page_content();
            }
        }
    }

    print_board();
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h * width + w] = ' ';
        }
    }

}


void Board::delete_page(int id, int job_index)
{
    int pop=0;
    for (int i = 0; i < idpage.size(); i++) {
        if (id == idpage[i].get_Page_id()) {
            pop = i;

            break;
        }
    }
    for (int i = 0; i < idpage.size(); i++) {
        if (id == idpage[i].get_Page_id()) {
            delete_pages(i);

            break;
        }
    }
    print_board();
    sort(idxvector.begin(), idxvector.end());
    for (int i = idxvector.size() - 1; i >= 0; i--) 
    {
        idpage.erase(idpage.begin() + idxvector[i]);
        idxvector.pop_back();
    }
    int order_num = order.size()-1;
    while (order_num >=0)
    {
        for (int h = idpage_for_print[order[order_num]].get_Page_y(); h < idpage_for_print[order[order_num]].get_Page_y() + idpage_for_print[order[order_num]].get_Page_height(); h++)
        {
            for (int w = idpage_for_print[order[order_num]].get_Page_x(); w < idpage_for_print[order[order_num]].get_Page_x() + idpage_for_print[order[order_num]].get_Page_width(); w++)
            {
                board[h * width + w] = idpage_for_print[order[order_num]].get_Page_content();
            }
        }

        print_board();
        order_num--;
    }
    for (int k =0 ; k < 0; k++)
    {
         for (int h = idpage_for_print[k].get_Page_y(); h < idpage_for_print[k].get_Page_y() + idpage_for_print[k].get_Page_height(); h++) 
         {
                for (int w = idpage_for_print[k].get_Page_x(); w < idpage_for_print[k].get_Page_x() + idpage_for_print[k].get_Page_width(); w++) 
                {
                    board[h * width + w] = idpage_for_print[k].get_Page_content();
                }
         }
        
        print_board();
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                board[h * width + w] = ' ';
            }
        }
    }
  
    return;

}


void Board::modify_content(int id, char content)
{


}
void Board::modify_position(int id, int x, int y) {



}

