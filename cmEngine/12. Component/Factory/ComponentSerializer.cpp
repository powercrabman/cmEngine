#include "0. cmEngine/cmEngine.h"
#include "ComponentSerializer.h"

cmEngine::ComponentSerializer::ComponentSerializer()
{
	EVENT_DISPATCHER.AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e) {Destroy(); });
}
