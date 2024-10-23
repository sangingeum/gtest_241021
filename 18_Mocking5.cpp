// 18_Mocking5.cpp
#include <iostream>

struct Packet { };

// C++ 에서는 암묵적인 인터페이스를 통한 의존성 주입 설계를 할 수 있습니다.
//  => C++ 단위 전략(Policy Based Design)
//  : 템플릿 기반으로 컴파일 시간에 정책을 교체할 수 있습니다.
//  => 인라인 최적화가 가능합니다.

class PacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "AppendPacket" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    template <typename IPacketStream>
    void ReadPacket(IPacketStream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
    }
};
//---
#include <gmock/gmock.h>

class MockPacketStream {
public:
    // void AppendPacket(Packet* newPacket)
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket));

    // const Packet* GetPacket(size_t packetNumber) const
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, ReadPacket)
{
    MockPacketStream stream;
    PacketReader reader;

    EXPECT_CALL(stream, AppendPacket(nullptr));
    EXPECT_CALL(stream, GetPacket(42));

    reader.ReadPacket(&stream, 42);
}

#if 0
int main()
{
    PacketStream stream;
    PacketReader reader;

    reader.ReadPacket(&stream, 42);
}
#endif
