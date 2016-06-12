#include "stdafx.h"
#include "MeshWindow.h"


MeshWindow::MeshWindow(wiGUI* gui) : GUI(gui)
{
	assert(GUI && "Invalid GUI!");

	float screenW = (float)wiRenderer::GetDevice()->GetScreenWidth();
	float screenH = (float)wiRenderer::GetDevice()->GetScreenHeight();


	meshWindow = new wiWindow(GUI, "Mesh Window");
	meshWindow->SetSize(XMFLOAT2(400, 300));
	meshWindow->SetEnabled(false);
	GUI->AddWidget(meshWindow);

	float x = 200;
	float y = 0;

	doubleSidedCheckBox = new wiCheckBox("Double Sided: ");
	doubleSidedCheckBox->SetPos(XMFLOAT2(x, y += 30));
	doubleSidedCheckBox->OnClick([&](wiEventArgs args) {
		if (mesh != nullptr)
		{
			mesh->doubleSided = args.bValue;
		}
	});
	meshWindow->AddWidget(doubleSidedCheckBox);

	massSlider = new wiSlider(0, 5000, 0, 100000, "Mass: ");
	massSlider->SetSize(XMFLOAT2(100, 30));
	massSlider->SetPos(XMFLOAT2(x, y += 30));
	massSlider->OnSlide([&](wiEventArgs args) {
		if (mesh != nullptr)
		{
			mesh->mass = args.fValue;
		}
	});
	meshWindow->AddWidget(massSlider);

	frictionSlider = new wiSlider(0, 5000, 0, 100000, "Friction: ");
	frictionSlider->SetSize(XMFLOAT2(100, 30));
	frictionSlider->SetPos(XMFLOAT2(x, y += 30));
	frictionSlider->OnSlide([&](wiEventArgs args) {
		if (mesh != nullptr)
		{
			mesh->friction = args.fValue;
		}
	});
	meshWindow->AddWidget(frictionSlider);




	meshWindow->Translate(XMFLOAT3(30, 30, 0));
	meshWindow->SetVisible(false);
}


MeshWindow::~MeshWindow()
{
	SAFE_DELETE(meshWindow);
	SAFE_DELETE(doubleSidedCheckBox);
	SAFE_DELETE(massSlider);
	SAFE_DELETE(frictionSlider);
}

void MeshWindow::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
	if (mesh != nullptr)
	{
		doubleSidedCheckBox->SetCheck(mesh->doubleSided);
		massSlider->SetValue(mesh->mass);
		frictionSlider->SetValue(mesh->friction);
		meshWindow->SetEnabled(true);
	}
	else
	{
		meshWindow->SetEnabled(false);
	}
}
