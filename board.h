#include <fstream>
#include <iostream>
#include <vector>
#include "page.h"


using namespace std;
vector<Page> idpage;


class Board {
public:
    Board(int num_jobs, int width, int height, ofstream& output_stream);
    ~Board();

    void print_board(int x, int y);
    void print_job(int job_idx, char job_type, int id);

    //job functions
    void insert_page(int x, int y, int width, int height, int id, char content);
    void delete_page(int id);
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


void Board::print_board(int x, int y) {
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


void Board::insert_page(int x, int y, int page_width, int page_height, int id, char content)//insert_page(0,1,10,15,c)
{
    for (int h = y; h < y + page_height; h++) {
        for (int w = x; w < x + page_width; w++) {
            board[h * width + w] = content;
        }
    }
    Page pg(x, y, page_width, page_height, id, content);
    idpage.push_back(pg);
    print_board(x, y);
}

void Board::delete_page(int id)
{

    for (int i = 0; i < idpage.size(); i++)
    {
        if (id == idpage[i].get_Page_id())
        {
            for (int j = idpage[i].get_Page_y(); j < idpage[i].get_Page_y() + idpage[i].get_Page_height(); j++)
            {
                for (int k = idpage[i].get_Page_x(); k < idpage[i].get_Page_x() + idpage[i].get_Page_width(); k++)
                {
                    board[j * width + k] = ' ';
                }
            }
            print_board(idpage[i].get_Page_x(), idpage[i].get_Page_y());
        }
    }

}

void Board::modify_content(int id, char content) {


}
void Board::modify_position(int id, int x, int y) {



}

