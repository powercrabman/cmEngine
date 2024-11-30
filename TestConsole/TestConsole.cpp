#include <iostream>
#include <functional>
#include "../Libraries/json/json.hpp"
#include "../Libraries/entt/entt.hpp"
using namespace std;
struct Pos { float x; };
struct Vec { float x; };
struct Money { float x; };

using json = nlohmann::json;
int main()
{
    entt::registry r{};
    for (int i=0;i<100;i++)
    {
        entt::entity e = static_cast<entt::entity>(10);
        if (!r.valid(e)) r.create(e);
    }

   auto view =  r.view<entt::entity>();
   for (auto e : view)
   {
       cout << (uint32_t)e << endl;
   }

    return 0;
}
