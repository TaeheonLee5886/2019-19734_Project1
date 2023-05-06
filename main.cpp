#include <iostream>
#include <fstream>
#include <string>
#include "board.h"

using namespace std;

void manage_board1() {

    int width, height;
    int num_jobs;
    char job_type;
    ifstream input;
    ofstream output;

    input.open("input_0.txt");

    if (!(input.is_open())) {
        cout << "Input missing" << endl;
        return;
    }

    input >> width >> height >> num_jobs;
    output.open("outputt.txt", ofstream::trunc);

    if (!(output.is_open())) {
        cout << "Output missing" << endl;
        return;
    }

    Board board = Board(num_jobs, width, height, output); //board.num_jobs=1, width=50, height=20;ofstream& output=output;



    int page_x, page_y, page_width, page_height, page_id;
    char page_content;

    for (int job_idx = 1; job_idx <= 7; job_idx++) {
        input >> job_type;
        switch (job_type) {
        case 'i':
            //insert page
            input >> page_id >> page_x >> page_y >> page_width >> page_height >> page_content;//id=8, x=0 y=1 width =10 height = 15 content =c
            //Page pgs=Page(page_x, page_y, page_width, page_height, job_idx, page_content);
            board.print_job(job_idx, job_type, page_id); //1,i,8
            board.insert_page(page_x, page_y, page_width, page_height, page_id, page_content);  //insert_page(0,1,10,15,c)
            break;
        case 'd':
            //delete page
            input >> page_id;
            board.print_job(job_idx, job_type, page_id);
            board.delete_page(page_id);
            output << "delete" << endl;
            break;
        case 'm':
            //modify page
            int modify_content;
            input >> modify_content;

            if (modify_content) {
                //modify content 
                input >> page_id >> page_content;
                board.print_job(job_idx, job_type, page_id);
                board.modify_content(page_id, page_content);
            }
            else {
                //modify position
                input >> page_id >> page_x >> page_y;
                board.print_job(job_idx, job_type, page_id);
                board.modify_position(page_id, page_x, page_y);
            }
            break;
        default:
            cout << "Wrong job type" << endl;
            return;
        }

        cout << "Job " << job_idx << " Complete!" << endl;

    }


    input.close();
    output.close();

}


int main(int argc, char* argv[]) {
    //if (argc==3) manage_board(string(argv[1]), string(argv[2]));
    //else cerr << "Wrong arguments" << endl;
    manage_board1();

    return 0;

}