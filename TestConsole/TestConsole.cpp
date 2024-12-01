#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <random>
#include "test.h"
#include <benchmark/benchmark.h>

std::vector<std::shared_ptr<Texture>> coreRepo;
std::vector<std::weak_ptr<Texture>> weakRepo;
std::vector<Handle<Texture>> handleRepo;
Store<Texture> store;

static void Renderer(Texture* inTex)
{
    // 백버퍼에 텍스처 데이터를 복사 (간단한 연산)
    uint32_t backbuffer[100][100] = {};
    std::fill(&backbuffer[0][0], &backbuffer[0][0] + 10000, inTex->pixelData);
}

// 1) weak_ptr을 사용한 벤치마크
static void BM_SharedPtr(benchmark::State& state) {
    for (auto _ : state)
    {
        int textureCount = state.range(0);

        // weak_ptr을 사용하여 텍스처 잠금
        for (int i = 0; i < textureCount; i++)
        {
            std::weak_ptr<Texture> tex = weakRepo[i];
            if (auto lockedTex = tex.lock()) {
                Renderer(lockedTex.get());
                benchmark::DoNotOptimize(lockedTex->pixelData);
            }
        }
    }
}

// 2) Store의 Handle을 사용한 벤치마크
static void BM_StoreHandle(benchmark::State& state) {
    for (auto _ : state)
    {
        int textureCount = state.range(0);

        // Store의 Handle을 사용하여 텍스처 가져오기
        for (int i = 0; i < textureCount; i++)
        {
            if (Texture* tex = store.TryGet(handleRepo[i])) {
                Renderer(tex);
                benchmark::DoNotOptimize(tex->pixelData);
            }
        }
    }
}

// 벤치마크 데이터 초기화
static void InitializeBenchmarkData(int textureCount) {
    coreRepo.clear();
    weakRepo.clear();
    handleRepo.clear();

    // coreRepo에 shared_ptr로 텍스처를 저장
    for (int i = 0; i < textureCount; ++i)
    {
        auto ptr = std::make_shared<Texture>(rand());
        coreRepo.push_back(ptr);
        weakRepo.push_back(ptr);  // shared_ptr과 연결된 weak_ptr 추가
    }

    // store에 Handle을 저장
    for (int i = 0; i < textureCount; ++i)
    {
        handleRepo.push_back(store.Create(Texture{ .pixelData = static_cast<uint32_t>(rand()) }));
    }

    // 벤치마크 데이터 섞기 (선택적으로 한 번만 실행)
    std::shuffle(weakRepo.begin(), weakRepo.end(), std::random_device{});
    std::shuffle(handleRepo.begin(), handleRepo.end(), std::random_device{});
}

// 벤치마크 설정
BENCHMARK(BM_StoreHandle)->Arg(100)->Arg(1000)->Arg(10000)->Arg(30000)->Arg(50000);
BENCHMARK(BM_SharedPtr)->Arg(100)->Arg(1000)->Arg(10000)->Arg(30000)->Arg(50000);

int main(int argc, char** argv) {
    // 벤치마크 데이터 초기화
    InitializeBenchmarkData(100000);

    // 벤치마크 초기화 및 실행
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}
