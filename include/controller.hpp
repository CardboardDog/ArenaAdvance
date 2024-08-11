#include "player.hpp"
namespace controllers{
    class controller{
        public:
           controller(players::player* player);
           void update();
        private:
            players::player* playerObj;
    };
}