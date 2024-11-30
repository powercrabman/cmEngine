#include "EnginePch.h"
#include "cmCommonCommand.h"
#include "cmRenderer.h"
#include "cmConsole.h"
#include "cmWindowsManager.h"
#include "cmWindow.h"
#include "cmConsoleGUI.h"

bool cmClearColorCmd::operator()(const std::vector<std::string>& inArgs) const
{
	std::vector<float> args = cmString::MapToFloat(inArgs);

	float r;
	float g;
	float b;
	float a;

	if (args.size() == 3)
	{
		r = args[0];
		g = args[1];
		b = args[2];
		a = 1.f;
	}
	else if (args.size() == 4)
	{
		r = args[0];
		g = args[1];
		b = args[2];
		a = args[3];
	}
	else
	{
		return false;
	}

	// [0, 255] 범위를 기대
	static constexpr float inv = 1 / 255.f;
	r *= inv;
	g *= inv;
	b *= inv;
	a *= inv;

	Engine->GetRenderer()->SetClearColor(Color{ r,g,b,a });
	return true;
}

const char* cmClearColorCmd::GetHelpDesc() const
{
	return "When clearing a render target, decide which color to clear it with. Enter R G B or R G B A in the range[0, 255] including spaces.";
}

const char* cmClearColorCmd::GetCommandText() const
{
	return "setclearcolor";
}

bool cmHelpCmd::operator()(const std::vector<std::string>& inArgs) const
{
	//Start
	Engine->GetConsole()->PushConsoleData("===========================");

	std::stringstream ss = {};
	const auto& cmdList = Engine->GetConsole()->GetCommandList();
	for (const auto& cmd : cmdList)
	{
		ss << cmd->GetCommandText() << " : " << cmd->GetHelpDesc();
		Engine->GetConsole()->PushConsoleData(ss.str());
		ss.str("");
	}

	//End
	Engine->GetConsole()->PushConsoleData("===========================");

	return true;
}

const char* cmHelpCmd::GetHelpDesc() const
{
	return "Shows a list of provided commands.";
}

const char* cmHelpCmd::GetCommandText() const
{
	return "help";
}

bool cmClearCmd::operator()(const std::vector<std::string>& inArgs) const
{
	Engine->GetConsole()->ClearConsoleDatas();
	return true;
}

const char* cmClearCmd::GetHelpDesc() const
{
	return "Clears all text displayed on the CLI screen.";
}

const char* cmClearCmd::GetCommandText() const
{
	return "clear";
}

bool cmExitCmd::operator()(const std::vector<std::string>& inArgs) const
{
	Engine->CloseGame();
	return true;
}

const char* cmExitCmd::GetHelpDesc() const
{
	return "Close the application.";
}

const char* cmExitCmd::GetCommandText() const
{
	return "exit";
}

bool cmSayCmd::operator()(const std::vector<std::string>& inArgs) const
{
	std::string inMsg = {};
	for (const auto& str : inArgs) inMsg.append(str + " ");

	Engine->GetConsole()->PushConsoleData(inMsg);
	return true;
}

const char* cmSayCmd::GetHelpDesc() const
{
	return "You can print messages to a command line window.";
}

const char* cmSayCmd::GetCommandText() const
{
	return "say";
}

bool cmResizeScreenCmd::operator()(const std::vector<std::string>& inArgs) const
{
	std::vector<float> args = cmString::MapToFloat(inArgs);

	if (args.size() == 2)
	{
		ScreenSize sc = {};
		sc.Width = args[0];
		sc.Height = args[1];

		Engine->GetWindowsManager()->GetMainWindow()->OnResize(sc);
		Engine->GetRenderer()->OnResize(sc);
		Engine->GetWindowsManager()->GetMainWindow()->Activate();

		return true;
	}

	return false;
}

const char* cmResizeScreenCmd::GetHelpDesc() const
{
	return "You can adjust the size of the main window by entering [width, height].";
}

const char* cmResizeScreenCmd::GetCommandText() const
{
	return "resizescreen";
}
