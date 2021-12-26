#include "Movable.h"
#include <iostream>
#include <math.h>

Movable::Movable()
{
	Tout = Eigen::Affine3d::Identity();
	Tin = Eigen::Affine3d::Identity();
}

Movable::Movable(const Movable& mov)
{
	Tout = mov.Tout;
	Tin = mov.Tin;
}

Eigen::Matrix4f Movable::MakeTransScale()
{
	return (Tout.matrix()*Tin.matrix()).cast<float>();
}

Eigen::Matrix4d Movable::MakeTransScaled()
{
	return (Tout.matrix() * Tin.matrix());
}


Eigen::Matrix4d Movable::MakeTransd()
{
	Eigen::Matrix4d mat = Eigen::Matrix4d::Identity();
	mat.col(3) << Tin.translation(), 1;

	return (Tout.matrix() * Tin.matrix());
}

void Movable::MyTranslate(Eigen::Vector3d amt, bool preRotation)
{
	
	if(preRotation)
		Tout.pretranslate(amt);
	else
		Tin.pretranslate(amt);
}
void Movable::TranslateInSystem(Eigen::Matrix3d rot, Eigen::Vector3d amt)
{
	Tout.pretranslate(rot.transpose()*amt);
}

void Movable::SetCenterOfRotation(Eigen::Vector3d amt)
{
	Tout.pretranslate(amt);
	Tin.pretranslate(-amt);
}
//angle in radians
void Movable::MyRotate(Eigen::Vector3d rotAxis, double angle)
{
	Tout.rotate(Eigen::AngleAxisd(angle, rotAxis.normalized()));
}

void Movable::RotateInSystem(Eigen::Vector3d rotAxis, double angle)
{
	
	Tout.rotate(Eigen::AngleAxisd(angle, Tout.rotation().transpose()*(rotAxis.normalized())));
}

void Movable::EulerRotation(double phi, double theta, double psi) {
	Eigen::Matrix3d A;
	double A00 = cos(psi)*cos(phi) - cos(theta)*sin(phi)*sin(psi);
	double A01 = -sin(psi)*cos(phi) - cos(theta)*sin(phi)*cos(psi);
	double A02 = sin(theta)*sin(phi);
	
	double A10 = cos(psi)*sin(phi) + cos(theta)*cos(phi)*sin(psi);
	double A11 = -sin(psi)*sin(phi) + cos(theta)*cos(phi)*cos(psi);
	double A12 = -sin(theta)*cos(phi);

	double A20 = sin(theta)*sin(psi);
	double A21 = sin(theta)*cos(psi);
	double A22 = cos(theta);

	A <<
		A00, A01, A02,
		A10, A11, A12,
		A20, A21, A22;

	Tout.rotate(A);
}

void Movable::MyRotate(const Eigen::Matrix3d& rot)
{
	Tout.rotate(rot);
}

void Movable::MyScale(Eigen::Vector3d amt)
{
	Tin.scale(amt);
}



























//void Movable::TranslateInSystem(Eigen::Matrix4d Mat, Eigen::Vector3d amt, bool preRotation)
//{
//	Eigen::Vector3d v = Mat.transpose().block<3, 3>(0, 0) * amt; //transpose instead of inverse
//	MyTranslate(v, preRotation);
//}
//
//void Movable::RotateInSystem(Eigen::Matrix4d Mat, Eigen::Vector3d rotAxis, double angle)
//{
//	Eigen::Vector3d v = Mat.transpose().block<3, 3>(0, 0) * rotAxis; //transpose instead of inverse
//	MyRotate(v.normalized(), angle);
//}
//
//
//void Movable::SetCenterOfRotation(Eigen::Vector3d amt)
//{
//	Tout.pretranslate(Tout.rotation().matrix().block<3, 3>(0, 0) * amt);
//	Tin.translate(-amt);
//}
//
//Eigen::Vector3d Movable::GetCenterOfRotation()
//{
//	return Tin.translation();
//}
