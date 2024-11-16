#include <iostream>
#include <fstream>
#include "../Libraries/json/json.hpp"
using json = nlohmann::json;

// Vector4 구조체 정의 및 JSON 매핑
struct Vector4
{
    float X, Y, Z, W;

    // Vector4의 JSON 변환 정의
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vector4, X, Y, Z, W)
};

// Player 구조체 정의 및 JSON 매핑
struct Player
{
    std::string Name;
    int Hp;

    // Player의 JSON 변환 정의
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player, Name, Hp)
};

struct Sex
{
    std::string gender;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Sex, gender);
};

int main()
{
    // JSON 데이터 구조 생성
    json js;

    // Player 객체 추가
    Player p;
    p.Name = "Jiwoo";
    p.Hp = 100;
    js["Player"] = p; // Player 객체를 JSON에 추가

    // Sex 객체 추가
    Sex s;
    s.gender = "Bozi";
    js["Sex"] = s; // Sex 객체를 JSON에 추가

    // Vector4 객체 추가
    Vector4 v;
    v.X = 1.0f;
    v.Y = 2.0f;
    v.Z = 3.0f;
    v.W = 4.0f;
    js["Vector"] = v; // Vector4 객체를 JSON에 추가

    // JSON 데이터를 파일로 저장
    std::ofstream ofs("Test.json");
    if (ofs.is_open())
    {
        ofs << js.dump(4); // JSON 데이터를 예쁘게 포맷팅하여 저장
        ofs.close();
    }
    else
    {
        std::cerr << "Failed to open file for writing." << std::endl;
    }

    return 0;
}
