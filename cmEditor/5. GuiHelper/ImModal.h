#pragma once

class ImModalOK
{
public:
	ImModalOK(std::string_view inCall)
		: mCall(inCall)
	{
	}

	void Open(std::string_view inMessage)
	{
		mMsg = inMessage;
		ImGui::OpenPopup(mCall.c_str());
	}

	void Draw() const
	{
		if (ImGui::BeginPopupModal(mCall.c_str(), nullptr, ImFlag::sModalFlag))
		{
			ImGui::TextUnformatted(mMsg.data());
			if (ImGui::Button("Okay")) { ImGui::CloseCurrentPopup(); }

			ImGui::EndPopup();
		}
	}

private:
	std::string mMsg;
	std::string mCall;
};

class ImModalYesOrNo
{
public:
	ImModalYesOrNo(std::string_view inCall)
		: mCall(inCall)
	{
	}

	void Open(std::string_view inMessage, const std::function<void()>& inYesCallback)
	{
		mMsg = inMessage;
		mYesCallback = inYesCallback;
		ImGui::OpenPopup(mCall.c_str());
	}

	void Draw() const
	{
		if (ImGui::BeginPopupModal(mCall.c_str(), nullptr, ImFlag::sModalFlag))
		{
			ImGui::TextUnformatted(mMsg.data());
			if (ImGui::Button("Yes")) { mYesCallback(); ImGui::CloseCurrentPopup(); }
			ImGui::SameLine();
			if (ImGui::Button("No")) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
	}

private:
	std::string mMsg;
	std::string mCall;
	std::function<void()> mYesCallback;
};
