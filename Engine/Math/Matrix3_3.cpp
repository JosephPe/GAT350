#include "Matrix3_3.h"

namespace anthemum
{
	// 1 0 0
	// 0 1 0
	// 0 0 1

	const Matrix3_3 Matrix3_3::identity
	{
		Vector3{1,0,0},
		Vector3{0,1,0},
		Vector3{0,0,1}
	};
	// 0 0 0
	// 0 0 0
	/// 0 0 0
	const Matrix3_3 Matrix3_3::zero
	{
		Vector3{0,0,0},
		Vector3{0,0,0},
		Vector3{0,0,0}
	};
}