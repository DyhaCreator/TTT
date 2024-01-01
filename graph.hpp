class Graph{
public:
    bool isOpen = true;
    const int Width = 1920;
    const int Height = 1080;
    sf::Event ev;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(Width, Height), "FNAA");
    Graph(){
        this->window.setFramerateLimit(60);
    }
    void update(){
        this->isOpen = this->window.isOpen();
        while(this->window.pollEvent(this->ev)){
            switch(this->ev.type){
            case sf::Event::Closed:
                this->window.close();
                break;
            }
        }
    }
    void render(){
        this->window.display();
        this->window.clear(sf::Color(100, 100, 100));
    }
};