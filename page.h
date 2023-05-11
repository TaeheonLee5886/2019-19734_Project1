
class Page {
    public:
        Page(int page_x, int page_y, int page_width, int page_height, int page_id, char page_content);
        int get_Page_id() { return id; }
        int get_Page_x() { return x; }
        int get_Page_y() { return y; }
        int get_Page_width() { return width; }
        int get_Page_height() { return height; }
        char get_Page_content() { return content; }
        void set_Page_content(char content_to_change) { content = content_to_change; }
        void set_Page_x(int page_x) { x = page_x; }
        void set_Page_y(int page_y) { y = page_y; }
        
        friend class board;


    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
};
Page::Page(int page_x, int page_y, int page_width, int page_height, int page_id, char page_content)
{
    x = page_x;
    y = page_y;
    width = page_width;
    height = page_height;
    id = page_id;
    content = page_content;

}
