#pragma once

// ���߿� ���� �޸� �Ҵ� ������ �ٲ� ����
// ����� ������ ����

namespace cmEngine
{
    // std::shared_ptr
    template<typename Ty>
    using Ref = std::shared_ptr<Ty>;

    template<typename Ty, typename ...Args>
    inline constexpr Ref<Ty> MakeRef(Args&&... args)
    {
        return std::make_shared<Ty>(std::forward<Args>(args)...);
    }

    // std::unique_ptr    
    template<typename Ty>
    using Scope = std::unique_ptr<Ty>;

    template<typename Ty, typename ...Args>
    inline constexpr Scope<Ty> MakeScope(Args&&... args)
    {
        return std::make_unique<Ty>(std::forward<Args>(args)...);
    }
}