#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <random>
#include "test.h"
#include <benchmark/benchmark.h>

// 전역 변수
std::unordered_map<std::string, std::shared_ptr<Texture>> sharedPtrTextures;
Store<Texture> store;

// 랜덤 선택 함수 (주어진 범위에서 랜덤으로 텍스처 선택)
template <typename T>
std::vector<T> GetRandomTextures(const std::unordered_map<std::string, T>& textureMap, int count) {
    std::vector<T> selectedTextures;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, textureMap.size() - 1);

    for (int i = 0; i < count; ++i) {
        auto it = std::next(textureMap.begin(), dis(gen));  // 랜덤한 위치로부터 텍스처 선택
        selectedTextures.push_back(it->second);
    }
    return selectedTextures;
}

// 1) 스마트 포인터(shared_ptr, weak_ptr)로 렌더링
static void BM_SharedPtr(benchmark::State& state) {
    for (auto _ : state) {
        // 랜덤하게 텍스처 선택 (100, 1000, 10000개 중 랜덤 선택)
        int textureCount = state.range(0);
        auto selectedTextures = GetRandomTextures(sharedPtrTextures, textureCount);

        for (auto& tex : selectedTextures) {
            std::weak_ptr<Texture> weakTex = tex;
            if (auto lockedTex = weakTex.lock()) {
                // 더미 연산 (고비용 연산을 인위적으로 추가)
                for (int i = 0; i < 1000; ++i) {
                    lockedTex->pixelData = (lockedTex->pixelData * 37 + 23) ^ 42;
                    lockedTex->pixelData ^= (lockedTex->pixelData << 13);
                    lockedTex->pixelData += (lockedTex->pixelData >> 7);
                    benchmark::DoNotOptimize(lockedTex->pixelData);
                }
            }
        }
    }
}

// 2) Store의 Handle로 렌더링
static void BM_StoreHandle(benchmark::State& state) {
    for (auto _ : state) {
        // 랜덤하게 텍스처 선택 (100, 1000, 10000개 중 랜덤 선택)
        int textureCount = state.range(0);
        std::vector<Handle<Texture>> selectedHandles;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, store.slotRepo.size() - 1);

        // 랜덤 핸들 생성
        for (int i = 0; i < textureCount; ++i) {
            int idx = dis(gen);  // 랜덤 인덱스 선택
            selectedHandles.push_back(Handle<Texture>{ (uint32_t)idx, store.slotRepo[idx].token });
        }

        // 렌더링
        for (auto& handleEntry : selectedHandles) {
            if (Texture* tex = store.TryGet(handleEntry)) {
                // 더미 연산 (고비용 연산을 인위적으로 추가)
                for (int i = 0; i < 1000; ++i) {
                    tex->pixelData = (tex->pixelData * 37 + 23) ^ 42;
                    tex->pixelData ^= (tex->pixelData << 13);
                    tex->pixelData += (tex->pixelData >> 7);
                    benchmark::DoNotOptimize(tex->pixelData);
                }
            }
        }
    }
}

// 3) shared_ptr 생성 및 삭제 시간 체크
static void BM_SharedPtrCreation(benchmark::State& state) {
    for (auto _ : state) {
        std::unordered_map<std::string, std::shared_ptr<Texture>> textureMap;
        for (int i = 0; i < state.range(0); ++i) {
            std::string name = "Texture_" + std::to_string(i);
            textureMap[name] = std::make_shared<Texture>();
        }
        // 삭제
        textureMap.clear();
    }
}

// 4) Store Handle 생성 및 삭제 시간 체크
static void BM_StoreHandleCreation(benchmark::State& state) {
    for (auto _ : state) {
        std::unordered_map<std::string, Handle<Texture>> handleMap;
        for (int i = 0; i < state.range(0); ++i) {
            std::string name = "Texture_" + std::to_string(i);
            Texture tex;
            tex.pixelData = 100;
            handleMap[name] = store.Create(name, tex);
        }

        // 삭제
        for (auto& handleEntry : handleMap) {
            store.TryRemove(handleEntry.second);
        }
    }
}

// 테스트 데이터 초기화
static void InitializeBenchmarkData(int textureCount) {
    // shared_ptr 텍스처 데이터 초기화
    sharedPtrTextures.clear();
    for (int i = 0; i < textureCount; ++i) {
        std::string name = "Texture_" + std::to_string(i);
        sharedPtrTextures[name] = std::make_shared<Texture>();
    }

    // Store 텍스처 데이터 초기화
    store = Store<Texture>();
    for (int i = 0; i < textureCount; ++i) {
        std::string name = "Texture_" + std::to_string(i);
        Texture tex;
        tex.pixelData = 100;
        store.Create(name, tex);
    }
}

// 벤치마크 등록
BENCHMARK(BM_SharedPtr)->Arg(100)->Arg(1000)->Arg(10000);
BENCHMARK(BM_StoreHandle)->Arg(100)->Arg(1000)->Arg(10000);
BENCHMARK(BM_SharedPtrCreation)->Arg(100)->Arg(1000)->Arg(10000);
BENCHMARK(BM_StoreHandleCreation)->Arg(100)->Arg(1000)->Arg(10000);

int main(int argc, char** argv) {
    // InitializeBenchmarkData 함수 호출 (벤치마크 전에 초기화)
    if (argc > 1) {
        int textureCount = std::stoi(argv[1]);
        InitializeBenchmarkData(textureCount); // textureCount를 초기화 데이터로 사용
    }
    else {
        InitializeBenchmarkData(50000); // 기본적으로 50000개의 텍스처로 초기화
    }

    // 벤치마크 초기화 및 실행
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
