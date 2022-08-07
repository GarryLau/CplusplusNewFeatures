#if 0
#include <iostream>
#include <string>
#include <vector>

namespace test_friend {
    
    class WindowMgr;
    
    class Screen {
    public:
        Screen() = default;
        Screen(const std::string& content): contents_(content){}
    private:
        std::string contents_;
        
        friend WindowMgr;
    };
    
    class WindowMgr {
    public:
        WindowMgr() = default;
        
        void add(const Screen& s) {
            screens_.push_back(s);
        }
        
        void show() const {
            for(int i = 0; i < screens_.size(); ++i) {
                std::cout << "index " << i << ": " << screens_[i].contents_ << std::endl;
            }
        }
        
        void clear(unsigned idx) {
            Screen& s = screens_[idx];
            s.contents_ = std::string("");
        }
    private:
        std::vector<Screen> screens_{Screen(std::string("IP"))};
    };
    

    auto main() -> int {
        WindowMgr winmgr;
        winmgr.add(Screen(std::string("Red Screen")));
        winmgr.add(Screen(std::string("Blue Screen")));        
        winmgr.clear(1);
        
        winmgr.show();

        return 0;
    }
}
#endif


#include <iostream>
#include <string>
#include <vector>

namespace test_friend {

    class Screen;
    class WindowMgr {
    public:
        WindowMgr() = default;
        
        void add(const Screen& s) {
            screens_.push_back(s);
        }
        
        inline void show();
        
        inline void clear(unsigned idx);
    private:
        std::vector<Screen> screens_;
    };
        
    class Screen {
    public:
        Screen() = default;
        Screen(const std::string& content): contents_(content){}
        void showContents() {
            std::cout << contents_ << std::endl;
        }
    private:
        std::string contents_{"IP"};
        
        friend void WindowMgr::clear(unsigned idx);
    };
    
    inline void WindowMgr::clear(unsigned idx) {
        Screen& s = screens_[idx];
        s.contents_ = std::string("");
    }
    
    inline void WindowMgr::show() {
        for(int i = 0; i < screens_.size(); ++i) {
            std::cout << "index " << i << ": ";
            screens_[i].showContents();
            std::cout << std::endl;
        }
    }

    auto main() -> int {
        WindowMgr winmgr;
        winmgr.add(Screen(std::string("Red Screen")));
        winmgr.add(Screen(std::string("Blue Screen")));        
        winmgr.add(Screen(std::string("Green Screen")));        
        winmgr.clear(1);
        
        winmgr.show();

        return 0;
    }
}
