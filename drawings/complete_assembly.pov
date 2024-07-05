#version 3.7; // 3.6
global_settings { assumed_gamma 1.0 }
#default { finish { ambient 0.2 diffuse 0.9 } }
#default { pigment { rgb <0.800, 0.800, 0.800> } }

//------------------------------------------
#include "colors.inc"
#include "textures.inc"

#include "rad_def.inc"
global_settings {
	radiosity {
		Rad_Settings(Radiosity_IndoorHQ, off, off)
	}
}
#default { finish{ ambient 0 } }

//------------------------------------------
#include "complete_assembly_textures.inc"
#include "complete_assembly_meshes.inc"

//------------------------------------------
// Camera ----------------------------------
#declare CamUp = < 0, 0, 492.80>;
#declare CamRight = <739.20, 0, 0>;
#declare CamRotation = <-90.0, 0.0, 0.0>;
#declare CamPosition = <203.47653198242188, -182.2257080078125, 1138.064208984375>;
camera {
	orthographic
	location <0, 0, 0>
	direction <0, 1, 0>
	up CamUp
	right CamRight
	rotate CamRotation
	translate CamPosition
}

// Background ------------------------------

polygon {
	5, <-369.5993957519531, -246.39959716796875>, <-369.5993957519531, 246.39959716796875>, <369.5993957519531, 246.39959716796875>, <369.5993957519531, -246.39959716796875>, <-369.5993957519531, -246.39959716796875>
	pigment {
		gradient y
		color_map {
			[ 0.00  color rgb<0.592, 0.592, 0.667> ]
			[ 0.05  color rgb<0.592, 0.592, 0.667> ]
			[ 0.95  color rgb<0.200, 0.200, 0.396> ]
			[ 1.00  color rgb<0.200, 0.200, 0.396> ]
		}
		scale <1,492.7991943359375,1>
		translate <0,-246.39959716796875,0>
	}
	finish { ambient 1 diffuse 0 }
	rotate <0.0, 0.0, 0.0>
	translate <203.47653198242188, -182.2257080078125, 1138.064208984375>
	translate <0.0, 0.0, -100000.0>
}
sky_sphere {
	pigment {
		gradient z
		color_map {
			[ 0.00  color rgb<0.592, 0.592, 0.667> ]
			[ 0.30  color rgb<0.592, 0.592, 0.667> ]
			[ 0.70  color rgb<0.200, 0.200, 0.396> ]
			[ 1.00  color rgb<0.200, 0.200, 0.396> ]
		}
		scale 2
		translate -1
		rotate<-90.0, 0.0, 0.0>
	}
}

//------------------------------------------

#include "complete_assembly_user.inc"

// Objects in Scene ------------------------

//----- X_Axis -----
//----- Y_Axis -----
//----- Z_Axis -----
//----- XY_Plane -----
//----- XZ_Plane -----
//----- Board_Geoms_7182 -----
//----- circuit_board -----
union {

	//----- Board_Geoms_7181 -----
	union {
	
		//----- Pcb_7181 -----
		object { Pcb_7181_mesh
				pigment { color rgb <0.200, 0.600, 0.400> }
		
		}
		
	}
	
	//----- Step_Models_7181 -----
	union {
	
		//----- Top_7181 -----
		union {
		
			//----- ${REFERENCE}_LED_D3_0mm_null -----
			object { ${REFERENCE}_LED_D3_0mm_null_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2] -----
			object { ${REFERENCE}_Body_null[2]_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null001 -----
			object { ${REFERENCE}_LED_D3_0mm_null001_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]001 -----
			object { ${REFERENCE}_Body_null[2]001_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null -----
			object { ${REFERENCE}_LED_D5_0mm_null_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null001 -----
			object { ${REFERENCE}_LED_D5_0mm_null001_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null002 -----
			object { ${REFERENCE}_LED_D5_0mm_null002_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null003 -----
			object { ${REFERENCE}_LED_D5_0mm_null003_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null004 -----
			object { ${REFERENCE}_LED_D5_0mm_null004_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null005 -----
			object { ${REFERENCE}_LED_D5_0mm_null005_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null006 -----
			object { ${REFERENCE}_LED_D5_0mm_null006_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null007 -----
			object { ${REFERENCE}_LED_D5_0mm_null007_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null008 -----
			object { ${REFERENCE}_LED_D5_0mm_null008_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null009 -----
			object { ${REFERENCE}_LED_D5_0mm_null009_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null002 -----
			object { ${REFERENCE}_LED_D3_0mm_null002_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]002 -----
			object { ${REFERENCE}_Body_null[2]002_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null010 -----
			object { ${REFERENCE}_LED_D5_0mm_null010_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null011 -----
			object { ${REFERENCE}_LED_D5_0mm_null011_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null003 -----
			object { ${REFERENCE}_LED_D3_0mm_null003_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]003 -----
			object { ${REFERENCE}_Body_null[2]003_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null004 -----
			object { ${REFERENCE}_LED_D3_0mm_null004_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]004 -----
			object { ${REFERENCE}_Body_null[2]004_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null012 -----
			object { ${REFERENCE}_LED_D5_0mm_null012_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null013 -----
			object { ${REFERENCE}_LED_D5_0mm_null013_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null014 -----
			object { ${REFERENCE}_LED_D5_0mm_null014_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null015 -----
			object { ${REFERENCE}_LED_D5_0mm_null015_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null016 -----
			object { ${REFERENCE}_LED_D5_0mm_null016_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null017 -----
			object { ${REFERENCE}_LED_D5_0mm_null017_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null -----
			object { ${REFERENCE}_R_0805_2012Metric_null_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null018 -----
			object { ${REFERENCE}_LED_D5_0mm_null018_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null019 -----
			object { ${REFERENCE}_LED_D5_0mm_null019_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null020 -----
			object { ${REFERENCE}_LED_D5_0mm_null020_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null005 -----
			object { ${REFERENCE}_LED_D3_0mm_null005_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]005 -----
			object { ${REFERENCE}_Body_null[2]005_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null021 -----
			object { ${REFERENCE}_LED_D5_0mm_null021_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null006 -----
			object { ${REFERENCE}_LED_D3_0mm_null006_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]006 -----
			object { ${REFERENCE}_Body_null[2]006_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null022 -----
			object { ${REFERENCE}_LED_D5_0mm_null022_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null007 -----
			object { ${REFERENCE}_LED_D3_0mm_null007_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]007 -----
			object { ${REFERENCE}_Body_null[2]007_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null008 -----
			object { ${REFERENCE}_LED_D3_0mm_null008_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]008 -----
			object { ${REFERENCE}_Body_null[2]008_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null009 -----
			object { ${REFERENCE}_LED_D3_0mm_null009_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]009 -----
			object { ${REFERENCE}_Body_null[2]009_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null023 -----
			object { ${REFERENCE}_LED_D5_0mm_null023_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null024 -----
			object { ${REFERENCE}_LED_D5_0mm_null024_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null025 -----
			object { ${REFERENCE}_LED_D5_0mm_null025_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null026 -----
			object { ${REFERENCE}_LED_D5_0mm_null026_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null010 -----
			object { ${REFERENCE}_LED_D3_0mm_null010_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]010 -----
			object { ${REFERENCE}_Body_null[2]010_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null011 -----
			object { ${REFERENCE}_LED_D3_0mm_null011_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]011 -----
			object { ${REFERENCE}_Body_null[2]011_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null027 -----
			object { ${REFERENCE}_LED_D5_0mm_null027_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null028 -----
			object { ${REFERENCE}_LED_D5_0mm_null028_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null012 -----
			object { ${REFERENCE}_LED_D3_0mm_null012_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]012 -----
			object { ${REFERENCE}_Body_null[2]012_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null029 -----
			object { ${REFERENCE}_LED_D5_0mm_null029_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null030 -----
			object { ${REFERENCE}_LED_D5_0mm_null030_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null031 -----
			object { ${REFERENCE}_LED_D5_0mm_null031_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null013 -----
			object { ${REFERENCE}_LED_D3_0mm_null013_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]013 -----
			object { ${REFERENCE}_Body_null[2]013_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null -----
			object { ${REFERENCE}_C_0805_2012Metric_null_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null032 -----
			object { ${REFERENCE}_LED_D5_0mm_null032_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null014 -----
			object { ${REFERENCE}_LED_D3_0mm_null014_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]014 -----
			object { ${REFERENCE}_Body_null[2]014_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null015 -----
			object { ${REFERENCE}_LED_D3_0mm_null015_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]015 -----
			object { ${REFERENCE}_Body_null[2]015_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null033 -----
			object { ${REFERENCE}_LED_D5_0mm_null033_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null034 -----
			object { ${REFERENCE}_LED_D5_0mm_null034_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null035 -----
			object { ${REFERENCE}_LED_D5_0mm_null035_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null016 -----
			object { ${REFERENCE}_LED_D3_0mm_null016_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]016 -----
			object { ${REFERENCE}_Body_null[2]016_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null017 -----
			object { ${REFERENCE}_LED_D3_0mm_null017_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]017 -----
			object { ${REFERENCE}_Body_null[2]017_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null036 -----
			object { ${REFERENCE}_LED_D5_0mm_null036_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null018 -----
			object { ${REFERENCE}_LED_D3_0mm_null018_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]018 -----
			object { ${REFERENCE}_Body_null[2]018_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null019 -----
			object { ${REFERENCE}_LED_D3_0mm_null019_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]019 -----
			object { ${REFERENCE}_Body_null[2]019_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null037 -----
			object { ${REFERENCE}_LED_D5_0mm_null037_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null020 -----
			object { ${REFERENCE}_LED_D3_0mm_null020_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]020 -----
			object { ${REFERENCE}_Body_null[2]020_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null001 -----
			object { ${REFERENCE}_R_0805_2012Metric_null001_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null021 -----
			object { ${REFERENCE}_LED_D3_0mm_null021_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]021 -----
			object { ${REFERENCE}_Body_null[2]021_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null002 -----
			object { ${REFERENCE}_R_0805_2012Metric_null002_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null038 -----
			object { ${REFERENCE}_LED_D5_0mm_null038_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null039 -----
			object { ${REFERENCE}_LED_D5_0mm_null039_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null040 -----
			object { ${REFERENCE}_LED_D5_0mm_null040_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null041 -----
			object { ${REFERENCE}_LED_D5_0mm_null041_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null022 -----
			object { ${REFERENCE}_LED_D3_0mm_null022_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]022 -----
			object { ${REFERENCE}_Body_null[2]022_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null042 -----
			object { ${REFERENCE}_LED_D5_0mm_null042_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null043 -----
			object { ${REFERENCE}_LED_D5_0mm_null043_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null044 -----
			object { ${REFERENCE}_LED_D5_0mm_null044_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null023 -----
			object { ${REFERENCE}_LED_D3_0mm_null023_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]023 -----
			object { ${REFERENCE}_Body_null[2]023_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null024 -----
			object { ${REFERENCE}_LED_D3_0mm_null024_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]024 -----
			object { ${REFERENCE}_Body_null[2]024_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null045 -----
			object { ${REFERENCE}_LED_D5_0mm_null045_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null046 -----
			object { ${REFERENCE}_LED_D5_0mm_null046_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null003 -----
			object { ${REFERENCE}_R_0805_2012Metric_null003_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null025 -----
			object { ${REFERENCE}_LED_D3_0mm_null025_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]025 -----
			object { ${REFERENCE}_Body_null[2]025_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null026 -----
			object { ${REFERENCE}_LED_D3_0mm_null026_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]026 -----
			object { ${REFERENCE}_Body_null[2]026_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null027 -----
			object { ${REFERENCE}_LED_D3_0mm_null027_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]027 -----
			object { ${REFERENCE}_Body_null[2]027_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null047 -----
			object { ${REFERENCE}_LED_D5_0mm_null047_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null048 -----
			object { ${REFERENCE}_LED_D5_0mm_null048_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null028 -----
			object { ${REFERENCE}_LED_D3_0mm_null028_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]028 -----
			object { ${REFERENCE}_Body_null[2]028_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null049 -----
			object { ${REFERENCE}_LED_D5_0mm_null049_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null050 -----
			object { ${REFERENCE}_LED_D5_0mm_null050_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null051 -----
			object { ${REFERENCE}_LED_D5_0mm_null051_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null029 -----
			object { ${REFERENCE}_LED_D3_0mm_null029_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]029 -----
			object { ${REFERENCE}_Body_null[2]029_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null052 -----
			object { ${REFERENCE}_LED_D5_0mm_null052_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null030 -----
			object { ${REFERENCE}_LED_D3_0mm_null030_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]030 -----
			object { ${REFERENCE}_Body_null[2]030_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null053 -----
			object { ${REFERENCE}_LED_D5_0mm_null053_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null031 -----
			object { ${REFERENCE}_LED_D3_0mm_null031_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]031 -----
			object { ${REFERENCE}_Body_null[2]031_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null032 -----
			object { ${REFERENCE}_LED_D3_0mm_null032_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]032 -----
			object { ${REFERENCE}_Body_null[2]032_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null033 -----
			object { ${REFERENCE}_LED_D3_0mm_null033_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]033 -----
			object { ${REFERENCE}_Body_null[2]033_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null054 -----
			object { ${REFERENCE}_LED_D5_0mm_null054_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null055 -----
			object { ${REFERENCE}_LED_D5_0mm_null055_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null004 -----
			object { ${REFERENCE}_R_0805_2012Metric_null004_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null056 -----
			object { ${REFERENCE}_LED_D5_0mm_null056_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null057 -----
			object { ${REFERENCE}_LED_D5_0mm_null057_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null058 -----
			object { ${REFERENCE}_LED_D5_0mm_null058_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null059 -----
			object { ${REFERENCE}_LED_D5_0mm_null059_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null060 -----
			object { ${REFERENCE}_LED_D5_0mm_null060_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null061 -----
			object { ${REFERENCE}_LED_D5_0mm_null061_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null001 -----
			object { ${REFERENCE}_C_0805_2012Metric_null001_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null034 -----
			object { ${REFERENCE}_LED_D3_0mm_null034_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]034 -----
			object { ${REFERENCE}_Body_null[2]034_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null062 -----
			object { ${REFERENCE}_LED_D5_0mm_null062_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null035 -----
			object { ${REFERENCE}_LED_D3_0mm_null035_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]035 -----
			object { ${REFERENCE}_Body_null[2]035_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null036 -----
			object { ${REFERENCE}_LED_D3_0mm_null036_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]036 -----
			object { ${REFERENCE}_Body_null[2]036_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null037 -----
			object { ${REFERENCE}_LED_D3_0mm_null037_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]037 -----
			object { ${REFERENCE}_Body_null[2]037_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null038 -----
			object { ${REFERENCE}_LED_D3_0mm_null038_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]038 -----
			object { ${REFERENCE}_Body_null[2]038_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null039 -----
			object { ${REFERENCE}_LED_D3_0mm_null039_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]039 -----
			object { ${REFERENCE}_Body_null[2]039_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null063 -----
			object { ${REFERENCE}_LED_D5_0mm_null063_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null040 -----
			object { ${REFERENCE}_LED_D3_0mm_null040_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]040 -----
			object { ${REFERENCE}_Body_null[2]040_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null064 -----
			object { ${REFERENCE}_LED_D5_0mm_null064_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null005 -----
			object { ${REFERENCE}_R_0805_2012Metric_null005_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null065 -----
			object { ${REFERENCE}_LED_D5_0mm_null065_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null041 -----
			object { ${REFERENCE}_LED_D3_0mm_null041_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]041 -----
			object { ${REFERENCE}_Body_null[2]041_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null066 -----
			object { ${REFERENCE}_LED_D5_0mm_null066_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null042 -----
			object { ${REFERENCE}_LED_D3_0mm_null042_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]042 -----
			object { ${REFERENCE}_Body_null[2]042_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null067 -----
			object { ${REFERENCE}_LED_D5_0mm_null067_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null068 -----
			object { ${REFERENCE}_LED_D5_0mm_null068_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null069 -----
			object { ${REFERENCE}_LED_D5_0mm_null069_mesh
			}
			
			//----- ${REFERENCE}_LED_0805_2012Metric_null -----
			object { ${REFERENCE}_LED_0805_2012Metric_null_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null043 -----
			object { ${REFERENCE}_LED_D3_0mm_null043_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]043 -----
			object { ${REFERENCE}_Body_null[2]043_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null002 -----
			object { ${REFERENCE}_C_0805_2012Metric_null002_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null070 -----
			object { ${REFERENCE}_LED_D5_0mm_null070_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null071 -----
			object { ${REFERENCE}_LED_D5_0mm_null071_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null072 -----
			object { ${REFERENCE}_LED_D5_0mm_null072_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null073 -----
			object { ${REFERENCE}_LED_D5_0mm_null073_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null044 -----
			object { ${REFERENCE}_LED_D3_0mm_null044_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]044 -----
			object { ${REFERENCE}_Body_null[2]044_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null074 -----
			object { ${REFERENCE}_LED_D5_0mm_null074_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null045 -----
			object { ${REFERENCE}_LED_D3_0mm_null045_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]045 -----
			object { ${REFERENCE}_Body_null[2]045_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null046 -----
			object { ${REFERENCE}_LED_D3_0mm_null046_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]046 -----
			object { ${REFERENCE}_Body_null[2]046_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null075 -----
			object { ${REFERENCE}_LED_D5_0mm_null075_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null076 -----
			object { ${REFERENCE}_LED_D5_0mm_null076_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null047 -----
			object { ${REFERENCE}_LED_D3_0mm_null047_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]047 -----
			object { ${REFERENCE}_Body_null[2]047_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null048 -----
			object { ${REFERENCE}_LED_D3_0mm_null048_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]048 -----
			object { ${REFERENCE}_Body_null[2]048_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null077 -----
			object { ${REFERENCE}_LED_D5_0mm_null077_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null078 -----
			object { ${REFERENCE}_LED_D5_0mm_null078_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null049 -----
			object { ${REFERENCE}_LED_D3_0mm_null049_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]049 -----
			object { ${REFERENCE}_Body_null[2]049_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null050 -----
			object { ${REFERENCE}_LED_D3_0mm_null050_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]050 -----
			object { ${REFERENCE}_Body_null[2]050_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null051 -----
			object { ${REFERENCE}_LED_D3_0mm_null051_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]051 -----
			object { ${REFERENCE}_Body_null[2]051_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null079 -----
			object { ${REFERENCE}_LED_D5_0mm_null079_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null052 -----
			object { ${REFERENCE}_LED_D3_0mm_null052_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]052 -----
			object { ${REFERENCE}_Body_null[2]052_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null080 -----
			object { ${REFERENCE}_LED_D5_0mm_null080_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null081 -----
			object { ${REFERENCE}_LED_D5_0mm_null081_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null082 -----
			object { ${REFERENCE}_LED_D5_0mm_null082_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null053 -----
			object { ${REFERENCE}_LED_D3_0mm_null053_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]053 -----
			object { ${REFERENCE}_Body_null[2]053_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null083 -----
			object { ${REFERENCE}_LED_D5_0mm_null083_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null084 -----
			object { ${REFERENCE}_LED_D5_0mm_null084_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null085 -----
			object { ${REFERENCE}_LED_D5_0mm_null085_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null054 -----
			object { ${REFERENCE}_LED_D3_0mm_null054_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]054 -----
			object { ${REFERENCE}_Body_null[2]054_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null086 -----
			object { ${REFERENCE}_LED_D5_0mm_null086_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null055 -----
			object { ${REFERENCE}_LED_D3_0mm_null055_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]055 -----
			object { ${REFERENCE}_Body_null[2]055_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null087 -----
			object { ${REFERENCE}_LED_D5_0mm_null087_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null056 -----
			object { ${REFERENCE}_LED_D3_0mm_null056_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]056 -----
			object { ${REFERENCE}_Body_null[2]056_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null088 -----
			object { ${REFERENCE}_LED_D5_0mm_null088_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null057 -----
			object { ${REFERENCE}_LED_D3_0mm_null057_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]057 -----
			object { ${REFERENCE}_Body_null[2]057_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null089 -----
			object { ${REFERENCE}_LED_D5_0mm_null089_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null058 -----
			object { ${REFERENCE}_LED_D3_0mm_null058_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]058 -----
			object { ${REFERENCE}_Body_null[2]058_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null090 -----
			object { ${REFERENCE}_LED_D5_0mm_null090_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null091 -----
			object { ${REFERENCE}_LED_D5_0mm_null091_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null092 -----
			object { ${REFERENCE}_LED_D5_0mm_null092_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null093 -----
			object { ${REFERENCE}_LED_D5_0mm_null093_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null094 -----
			object { ${REFERENCE}_LED_D5_0mm_null094_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null095 -----
			object { ${REFERENCE}_LED_D5_0mm_null095_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null096 -----
			object { ${REFERENCE}_LED_D5_0mm_null096_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null097 -----
			object { ${REFERENCE}_LED_D5_0mm_null097_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null059 -----
			object { ${REFERENCE}_LED_D3_0mm_null059_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]059 -----
			object { ${REFERENCE}_Body_null[2]059_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null060 -----
			object { ${REFERENCE}_LED_D3_0mm_null060_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]060 -----
			object { ${REFERENCE}_Body_null[2]060_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null098 -----
			object { ${REFERENCE}_LED_D5_0mm_null098_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null099 -----
			object { ${REFERENCE}_LED_D5_0mm_null099_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null061 -----
			object { ${REFERENCE}_LED_D3_0mm_null061_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]061 -----
			object { ${REFERENCE}_Body_null[2]061_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null006 -----
			object { ${REFERENCE}_R_0805_2012Metric_null006_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null100 -----
			object { ${REFERENCE}_LED_D5_0mm_null100_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null062 -----
			object { ${REFERENCE}_LED_D3_0mm_null062_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]062 -----
			object { ${REFERENCE}_Body_null[2]062_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null101 -----
			object { ${REFERENCE}_LED_D5_0mm_null101_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null003 -----
			object { ${REFERENCE}_C_0805_2012Metric_null003_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null102 -----
			object { ${REFERENCE}_LED_D5_0mm_null102_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null103 -----
			object { ${REFERENCE}_LED_D5_0mm_null103_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null104 -----
			object { ${REFERENCE}_LED_D5_0mm_null104_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null063 -----
			object { ${REFERENCE}_LED_D3_0mm_null063_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]063 -----
			object { ${REFERENCE}_Body_null[2]063_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null105 -----
			object { ${REFERENCE}_LED_D5_0mm_null105_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null004 -----
			object { ${REFERENCE}_C_0805_2012Metric_null004_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null064 -----
			object { ${REFERENCE}_LED_D3_0mm_null064_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]064 -----
			object { ${REFERENCE}_Body_null[2]064_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null106 -----
			object { ${REFERENCE}_LED_D5_0mm_null106_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null107 -----
			object { ${REFERENCE}_LED_D5_0mm_null107_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null065 -----
			object { ${REFERENCE}_LED_D3_0mm_null065_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]065 -----
			object { ${REFERENCE}_Body_null[2]065_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null108 -----
			object { ${REFERENCE}_LED_D5_0mm_null108_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null066 -----
			object { ${REFERENCE}_LED_D3_0mm_null066_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]066 -----
			object { ${REFERENCE}_Body_null[2]066_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null109 -----
			object { ${REFERENCE}_LED_D5_0mm_null109_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null067 -----
			object { ${REFERENCE}_LED_D3_0mm_null067_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]067 -----
			object { ${REFERENCE}_Body_null[2]067_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null007 -----
			object { ${REFERENCE}_R_0805_2012Metric_null007_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null110 -----
			object { ${REFERENCE}_LED_D5_0mm_null110_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null111 -----
			object { ${REFERENCE}_LED_D5_0mm_null111_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null112 -----
			object { ${REFERENCE}_LED_D5_0mm_null112_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null005 -----
			object { ${REFERENCE}_C_0805_2012Metric_null005_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null113 -----
			object { ${REFERENCE}_LED_D5_0mm_null113_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null008 -----
			object { ${REFERENCE}_R_0805_2012Metric_null008_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null114 -----
			object { ${REFERENCE}_LED_D5_0mm_null114_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null115 -----
			object { ${REFERENCE}_LED_D5_0mm_null115_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null006 -----
			object { ${REFERENCE}_C_0805_2012Metric_null006_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null116 -----
			object { ${REFERENCE}_LED_D5_0mm_null116_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null117 -----
			object { ${REFERENCE}_LED_D5_0mm_null117_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null068 -----
			object { ${REFERENCE}_LED_D3_0mm_null068_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]068 -----
			object { ${REFERENCE}_Body_null[2]068_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null069 -----
			object { ${REFERENCE}_LED_D3_0mm_null069_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]069 -----
			object { ${REFERENCE}_Body_null[2]069_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null118 -----
			object { ${REFERENCE}_LED_D5_0mm_null118_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null119 -----
			object { ${REFERENCE}_LED_D5_0mm_null119_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null070 -----
			object { ${REFERENCE}_LED_D3_0mm_null070_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]070 -----
			object { ${REFERENCE}_Body_null[2]070_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null007 -----
			object { ${REFERENCE}_C_0805_2012Metric_null007_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null120 -----
			object { ${REFERENCE}_LED_D5_0mm_null120_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null071 -----
			object { ${REFERENCE}_LED_D3_0mm_null071_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]071 -----
			object { ${REFERENCE}_Body_null[2]071_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null121 -----
			object { ${REFERENCE}_LED_D5_0mm_null121_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null122 -----
			object { ${REFERENCE}_LED_D5_0mm_null122_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null123 -----
			object { ${REFERENCE}_LED_D5_0mm_null123_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null124 -----
			object { ${REFERENCE}_LED_D5_0mm_null124_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null072 -----
			object { ${REFERENCE}_LED_D3_0mm_null072_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]072 -----
			object { ${REFERENCE}_Body_null[2]072_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null125 -----
			object { ${REFERENCE}_LED_D5_0mm_null125_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null126 -----
			object { ${REFERENCE}_LED_D5_0mm_null126_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null073 -----
			object { ${REFERENCE}_LED_D3_0mm_null073_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]073 -----
			object { ${REFERENCE}_Body_null[2]073_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null074 -----
			object { ${REFERENCE}_LED_D3_0mm_null074_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]074 -----
			object { ${REFERENCE}_Body_null[2]074_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null127 -----
			object { ${REFERENCE}_LED_D5_0mm_null127_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null075 -----
			object { ${REFERENCE}_LED_D3_0mm_null075_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]075 -----
			object { ${REFERENCE}_Body_null[2]075_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null076 -----
			object { ${REFERENCE}_LED_D3_0mm_null076_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]076 -----
			object { ${REFERENCE}_Body_null[2]076_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null128 -----
			object { ${REFERENCE}_LED_D5_0mm_null128_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null129 -----
			object { ${REFERENCE}_LED_D5_0mm_null129_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null077 -----
			object { ${REFERENCE}_LED_D3_0mm_null077_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]077 -----
			object { ${REFERENCE}_Body_null[2]077_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null130 -----
			object { ${REFERENCE}_LED_D5_0mm_null130_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null078 -----
			object { ${REFERENCE}_LED_D3_0mm_null078_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]078 -----
			object { ${REFERENCE}_Body_null[2]078_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null131 -----
			object { ${REFERENCE}_LED_D5_0mm_null131_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null132 -----
			object { ${REFERENCE}_LED_D5_0mm_null132_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null133 -----
			object { ${REFERENCE}_LED_D5_0mm_null133_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null134 -----
			object { ${REFERENCE}_LED_D5_0mm_null134_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null135 -----
			object { ${REFERENCE}_LED_D5_0mm_null135_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null136 -----
			object { ${REFERENCE}_LED_D5_0mm_null136_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null079 -----
			object { ${REFERENCE}_LED_D3_0mm_null079_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]079 -----
			object { ${REFERENCE}_Body_null[2]079_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null080 -----
			object { ${REFERENCE}_LED_D3_0mm_null080_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]080 -----
			object { ${REFERENCE}_Body_null[2]080_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null081 -----
			object { ${REFERENCE}_LED_D3_0mm_null081_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]081 -----
			object { ${REFERENCE}_Body_null[2]081_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null082 -----
			object { ${REFERENCE}_LED_D3_0mm_null082_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]082 -----
			object { ${REFERENCE}_Body_null[2]082_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null137 -----
			object { ${REFERENCE}_LED_D5_0mm_null137_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null138 -----
			object { ${REFERENCE}_LED_D5_0mm_null138_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null139 -----
			object { ${REFERENCE}_LED_D5_0mm_null139_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null083 -----
			object { ${REFERENCE}_LED_D3_0mm_null083_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]083 -----
			object { ${REFERENCE}_Body_null[2]083_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null140 -----
			object { ${REFERENCE}_LED_D5_0mm_null140_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null141 -----
			object { ${REFERENCE}_LED_D5_0mm_null141_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null084 -----
			object { ${REFERENCE}_LED_D3_0mm_null084_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]084 -----
			object { ${REFERENCE}_Body_null[2]084_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_0805_2012Metric_null001 -----
			object { ${REFERENCE}_LED_0805_2012Metric_null001_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null085 -----
			object { ${REFERENCE}_LED_D3_0mm_null085_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]085 -----
			object { ${REFERENCE}_Body_null[2]085_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null008 -----
			object { ${REFERENCE}_C_0805_2012Metric_null008_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null086 -----
			object { ${REFERENCE}_LED_D3_0mm_null086_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]086 -----
			object { ${REFERENCE}_Body_null[2]086_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null142 -----
			object { ${REFERENCE}_LED_D5_0mm_null142_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null087 -----
			object { ${REFERENCE}_LED_D3_0mm_null087_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]087 -----
			object { ${REFERENCE}_Body_null[2]087_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null143 -----
			object { ${REFERENCE}_LED_D5_0mm_null143_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null144 -----
			object { ${REFERENCE}_LED_D5_0mm_null144_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null145 -----
			object { ${REFERENCE}_LED_D5_0mm_null145_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null088 -----
			object { ${REFERENCE}_LED_D3_0mm_null088_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]088 -----
			object { ${REFERENCE}_Body_null[2]088_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null146 -----
			object { ${REFERENCE}_LED_D5_0mm_null146_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null147 -----
			object { ${REFERENCE}_LED_D5_0mm_null147_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null089 -----
			object { ${REFERENCE}_LED_D3_0mm_null089_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]089 -----
			object { ${REFERENCE}_Body_null[2]089_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null090 -----
			object { ${REFERENCE}_LED_D3_0mm_null090_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]090 -----
			object { ${REFERENCE}_Body_null[2]090_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null148 -----
			object { ${REFERENCE}_LED_D5_0mm_null148_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null149 -----
			object { ${REFERENCE}_LED_D5_0mm_null149_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null091 -----
			object { ${REFERENCE}_LED_D3_0mm_null091_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]091 -----
			object { ${REFERENCE}_Body_null[2]091_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null150 -----
			object { ${REFERENCE}_LED_D5_0mm_null150_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null092 -----
			object { ${REFERENCE}_LED_D3_0mm_null092_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]092 -----
			object { ${REFERENCE}_Body_null[2]092_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null093 -----
			object { ${REFERENCE}_LED_D3_0mm_null093_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]093 -----
			object { ${REFERENCE}_Body_null[2]093_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null094 -----
			object { ${REFERENCE}_LED_D3_0mm_null094_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]094 -----
			object { ${REFERENCE}_Body_null[2]094_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null095 -----
			object { ${REFERENCE}_LED_D3_0mm_null095_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]095 -----
			object { ${REFERENCE}_Body_null[2]095_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null096 -----
			object { ${REFERENCE}_LED_D3_0mm_null096_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]096 -----
			object { ${REFERENCE}_Body_null[2]096_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_0805_2012Metric_null002 -----
			object { ${REFERENCE}_LED_0805_2012Metric_null002_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null009 -----
			object { ${REFERENCE}_R_0805_2012Metric_null009_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null097 -----
			object { ${REFERENCE}_LED_D3_0mm_null097_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]097 -----
			object { ${REFERENCE}_Body_null[2]097_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null098 -----
			object { ${REFERENCE}_LED_D3_0mm_null098_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]098 -----
			object { ${REFERENCE}_Body_null[2]098_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null099 -----
			object { ${REFERENCE}_LED_D3_0mm_null099_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]099 -----
			object { ${REFERENCE}_Body_null[2]099_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null100 -----
			object { ${REFERENCE}_LED_D3_0mm_null100_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]100 -----
			object { ${REFERENCE}_Body_null[2]100_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null151 -----
			object { ${REFERENCE}_LED_D5_0mm_null151_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null152 -----
			object { ${REFERENCE}_LED_D5_0mm_null152_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null153 -----
			object { ${REFERENCE}_LED_D5_0mm_null153_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null154 -----
			object { ${REFERENCE}_LED_D5_0mm_null154_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null155 -----
			object { ${REFERENCE}_LED_D5_0mm_null155_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null101 -----
			object { ${REFERENCE}_LED_D3_0mm_null101_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]101 -----
			object { ${REFERENCE}_Body_null[2]101_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null009 -----
			object { ${REFERENCE}_C_0805_2012Metric_null009_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null156 -----
			object { ${REFERENCE}_LED_D5_0mm_null156_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null102 -----
			object { ${REFERENCE}_LED_D3_0mm_null102_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]102 -----
			object { ${REFERENCE}_Body_null[2]102_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null103 -----
			object { ${REFERENCE}_LED_D3_0mm_null103_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]103 -----
			object { ${REFERENCE}_Body_null[2]103_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null157 -----
			object { ${REFERENCE}_LED_D5_0mm_null157_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null158 -----
			object { ${REFERENCE}_LED_D5_0mm_null158_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null104 -----
			object { ${REFERENCE}_LED_D3_0mm_null104_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]104 -----
			object { ${REFERENCE}_Body_null[2]104_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null159 -----
			object { ${REFERENCE}_LED_D5_0mm_null159_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null010 -----
			object { ${REFERENCE}_C_0805_2012Metric_null010_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null105 -----
			object { ${REFERENCE}_LED_D3_0mm_null105_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]105 -----
			object { ${REFERENCE}_Body_null[2]105_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null160 -----
			object { ${REFERENCE}_LED_D5_0mm_null160_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null161 -----
			object { ${REFERENCE}_LED_D5_0mm_null161_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null162 -----
			object { ${REFERENCE}_LED_D5_0mm_null162_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null163 -----
			object { ${REFERENCE}_LED_D5_0mm_null163_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null164 -----
			object { ${REFERENCE}_LED_D5_0mm_null164_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null106 -----
			object { ${REFERENCE}_LED_D3_0mm_null106_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]106 -----
			object { ${REFERENCE}_Body_null[2]106_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null165 -----
			object { ${REFERENCE}_LED_D5_0mm_null165_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null166 -----
			object { ${REFERENCE}_LED_D5_0mm_null166_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null167 -----
			object { ${REFERENCE}_LED_D5_0mm_null167_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null168 -----
			object { ${REFERENCE}_LED_D5_0mm_null168_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null169 -----
			object { ${REFERENCE}_LED_D5_0mm_null169_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null170 -----
			object { ${REFERENCE}_LED_D5_0mm_null170_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null107 -----
			object { ${REFERENCE}_LED_D3_0mm_null107_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]107 -----
			object { ${REFERENCE}_Body_null[2]107_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null108 -----
			object { ${REFERENCE}_LED_D3_0mm_null108_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]108 -----
			object { ${REFERENCE}_Body_null[2]108_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null109 -----
			object { ${REFERENCE}_LED_D3_0mm_null109_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]109 -----
			object { ${REFERENCE}_Body_null[2]109_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null171 -----
			object { ${REFERENCE}_LED_D5_0mm_null171_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null172 -----
			object { ${REFERENCE}_LED_D5_0mm_null172_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null173 -----
			object { ${REFERENCE}_LED_D5_0mm_null173_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null010 -----
			object { ${REFERENCE}_R_0805_2012Metric_null010_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null110 -----
			object { ${REFERENCE}_LED_D3_0mm_null110_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]110 -----
			object { ${REFERENCE}_Body_null[2]110_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null174 -----
			object { ${REFERENCE}_LED_D5_0mm_null174_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null175 -----
			object { ${REFERENCE}_LED_D5_0mm_null175_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null011 -----
			object { ${REFERENCE}_C_0805_2012Metric_null011_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null176 -----
			object { ${REFERENCE}_LED_D5_0mm_null176_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null177 -----
			object { ${REFERENCE}_LED_D5_0mm_null177_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null111 -----
			object { ${REFERENCE}_LED_D3_0mm_null111_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]111 -----
			object { ${REFERENCE}_Body_null[2]111_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null178 -----
			object { ${REFERENCE}_LED_D5_0mm_null178_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null179 -----
			object { ${REFERENCE}_LED_D5_0mm_null179_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null180 -----
			object { ${REFERENCE}_LED_D5_0mm_null180_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null181 -----
			object { ${REFERENCE}_LED_D5_0mm_null181_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null182 -----
			object { ${REFERENCE}_LED_D5_0mm_null182_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null112 -----
			object { ${REFERENCE}_LED_D3_0mm_null112_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]112 -----
			object { ${REFERENCE}_Body_null[2]112_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null113 -----
			object { ${REFERENCE}_LED_D3_0mm_null113_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]113 -----
			object { ${REFERENCE}_Body_null[2]113_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null183 -----
			object { ${REFERENCE}_LED_D5_0mm_null183_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null114 -----
			object { ${REFERENCE}_LED_D3_0mm_null114_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]114 -----
			object { ${REFERENCE}_Body_null[2]114_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null184 -----
			object { ${REFERENCE}_LED_D5_0mm_null184_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null185 -----
			object { ${REFERENCE}_LED_D5_0mm_null185_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null186 -----
			object { ${REFERENCE}_LED_D5_0mm_null186_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null115 -----
			object { ${REFERENCE}_LED_D3_0mm_null115_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]115 -----
			object { ${REFERENCE}_Body_null[2]115_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null116 -----
			object { ${REFERENCE}_LED_D3_0mm_null116_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]116 -----
			object { ${REFERENCE}_Body_null[2]116_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null187 -----
			object { ${REFERENCE}_LED_D5_0mm_null187_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null188 -----
			object { ${REFERENCE}_LED_D5_0mm_null188_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null117 -----
			object { ${REFERENCE}_LED_D3_0mm_null117_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]117 -----
			object { ${REFERENCE}_Body_null[2]117_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null189 -----
			object { ${REFERENCE}_LED_D5_0mm_null189_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null118 -----
			object { ${REFERENCE}_LED_D3_0mm_null118_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]118 -----
			object { ${REFERENCE}_Body_null[2]118_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null190 -----
			object { ${REFERENCE}_LED_D5_0mm_null190_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null119 -----
			object { ${REFERENCE}_LED_D3_0mm_null119_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]119 -----
			object { ${REFERENCE}_Body_null[2]119_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null191 -----
			object { ${REFERENCE}_LED_D5_0mm_null191_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null120 -----
			object { ${REFERENCE}_LED_D3_0mm_null120_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]120 -----
			object { ${REFERENCE}_Body_null[2]120_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_0805_2012Metric_null003 -----
			object { ${REFERENCE}_LED_0805_2012Metric_null003_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null192 -----
			object { ${REFERENCE}_LED_D5_0mm_null192_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null121 -----
			object { ${REFERENCE}_LED_D3_0mm_null121_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]121 -----
			object { ${REFERENCE}_Body_null[2]121_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null193 -----
			object { ${REFERENCE}_LED_D5_0mm_null193_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null194 -----
			object { ${REFERENCE}_LED_D5_0mm_null194_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null195 -----
			object { ${REFERENCE}_LED_D5_0mm_null195_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null196 -----
			object { ${REFERENCE}_LED_D5_0mm_null196_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null122 -----
			object { ${REFERENCE}_LED_D3_0mm_null122_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]122 -----
			object { ${REFERENCE}_Body_null[2]122_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null123 -----
			object { ${REFERENCE}_LED_D3_0mm_null123_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]123 -----
			object { ${REFERENCE}_Body_null[2]123_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null124 -----
			object { ${REFERENCE}_LED_D3_0mm_null124_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]124 -----
			object { ${REFERENCE}_Body_null[2]124_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null197 -----
			object { ${REFERENCE}_LED_D5_0mm_null197_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null198 -----
			object { ${REFERENCE}_LED_D5_0mm_null198_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null199 -----
			object { ${REFERENCE}_LED_D5_0mm_null199_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null200 -----
			object { ${REFERENCE}_LED_D5_0mm_null200_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null201 -----
			object { ${REFERENCE}_LED_D5_0mm_null201_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null125 -----
			object { ${REFERENCE}_LED_D3_0mm_null125_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]125 -----
			object { ${REFERENCE}_Body_null[2]125_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null202 -----
			object { ${REFERENCE}_LED_D5_0mm_null202_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null203 -----
			object { ${REFERENCE}_LED_D5_0mm_null203_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null126 -----
			object { ${REFERENCE}_LED_D3_0mm_null126_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]126 -----
			object { ${REFERENCE}_Body_null[2]126_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null204 -----
			object { ${REFERENCE}_LED_D5_0mm_null204_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null127 -----
			object { ${REFERENCE}_LED_D3_0mm_null127_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]127 -----
			object { ${REFERENCE}_Body_null[2]127_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null128 -----
			object { ${REFERENCE}_LED_D3_0mm_null128_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]128 -----
			object { ${REFERENCE}_Body_null[2]128_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null205 -----
			object { ${REFERENCE}_LED_D5_0mm_null205_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null129 -----
			object { ${REFERENCE}_LED_D3_0mm_null129_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]129 -----
			object { ${REFERENCE}_Body_null[2]129_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null130 -----
			object { ${REFERENCE}_LED_D3_0mm_null130_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]130 -----
			object { ${REFERENCE}_Body_null[2]130_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null131 -----
			object { ${REFERENCE}_LED_D3_0mm_null131_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]131 -----
			object { ${REFERENCE}_Body_null[2]131_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null206 -----
			object { ${REFERENCE}_LED_D5_0mm_null206_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null132 -----
			object { ${REFERENCE}_LED_D3_0mm_null132_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]132 -----
			object { ${REFERENCE}_Body_null[2]132_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null133 -----
			object { ${REFERENCE}_LED_D3_0mm_null133_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]133 -----
			object { ${REFERENCE}_Body_null[2]133_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null134 -----
			object { ${REFERENCE}_LED_D3_0mm_null134_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]134 -----
			object { ${REFERENCE}_Body_null[2]134_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null207 -----
			object { ${REFERENCE}_LED_D5_0mm_null207_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null208 -----
			object { ${REFERENCE}_LED_D5_0mm_null208_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null135 -----
			object { ${REFERENCE}_LED_D3_0mm_null135_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]135 -----
			object { ${REFERENCE}_Body_null[2]135_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null136 -----
			object { ${REFERENCE}_LED_D3_0mm_null136_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]136 -----
			object { ${REFERENCE}_Body_null[2]136_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null209 -----
			object { ${REFERENCE}_LED_D5_0mm_null209_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null012 -----
			object { ${REFERENCE}_C_0805_2012Metric_null012_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null210 -----
			object { ${REFERENCE}_LED_D5_0mm_null210_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null137 -----
			object { ${REFERENCE}_LED_D3_0mm_null137_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]137 -----
			object { ${REFERENCE}_Body_null[2]137_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null211 -----
			object { ${REFERENCE}_LED_D5_0mm_null211_mesh
			}
			
			//----- ${REFERENCE}_VEML7700_TR_null -----
			object { ${REFERENCE}_VEML7700_TR_null_mesh
					pigment { color rgb <0.792, 0.820, 0.933> }
			
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null138 -----
			object { ${REFERENCE}_LED_D3_0mm_null138_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]138 -----
			object { ${REFERENCE}_Body_null[2]138_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null212 -----
			object { ${REFERENCE}_LED_D5_0mm_null212_mesh
			}
			
			//----- ${REFERENCE}_LED_D5_0mm_null213 -----
			object { ${REFERENCE}_LED_D5_0mm_null213_mesh
			}
			
			//----- ${REFERENCE}_LED_D3_0mm_null139 -----
			object { ${REFERENCE}_LED_D3_0mm_null139_mesh
			}
			
			//----- ${REFERENCE}_Body_null[2]139 -----
			object { ${REFERENCE}_Body_null[2]139_mesh
					pigment { color rgb <0.957, 0.957, 0.957> }
			
			}
			
		}
		
		//----- Bot_7181 -----
		union {
		
			//----- ${REFERENCE}_R_0805_2012Metric_null011 -----
			object { ${REFERENCE}_R_0805_2012Metric_null011_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null012 -----
			object { ${REFERENCE}_R_0805_2012Metric_null012_mesh
			}
			
			//----- ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null -----
			object { ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null_mesh
			}
			
			//----- ${REFERENCE}_SOT_223_null -----
			object { ${REFERENCE}_SOT_223_null_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null013 -----
			object { ${REFERENCE}_R_0805_2012Metric_null013_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null013 -----
			object { ${REFERENCE}_C_0805_2012Metric_null013_mesh
			}
			
			//----- ${REFERENCE}_Keystone_1058_1x2032_null -----
			object { ${REFERENCE}_Keystone_1058_1x2032_null_mesh
			}
			
			//----- ${REFERENCE}_CP_Elec_18x175_null -----
			object { ${REFERENCE}_CP_Elec_18x175_null_mesh
			}
			
			//----- ${REFERENCE}_SW_SPST_TL3301_6x6mm_H4_3mm_null -----
			object { ${REFERENCE}_SW_SPST_TL3301_6x6mm_H4_3mm_null_mesh
					pigment { color rgb <0.388, 0.310, 0.129> }
			
			}
			
			//----- ${REFERENCE}_SMA_Amphenol_132291_12_Vertical_null -----
			object { ${REFERENCE}_SMA_Amphenol_132291_12_Vertical_null_mesh
			}
			
			//----- ${REFERENCE}_SOT_223_null001 -----
			object { ${REFERENCE}_SOT_223_null001_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null014 -----
			object { ${REFERENCE}_R_0805_2012Metric_null014_mesh
			}
			
			//----- ${REFERENCE}_ESP32_WROVER_B_null -----
			object { ${REFERENCE}_ESP32_WROVER_B_null_mesh
					pigment { color rgb <0.792, 0.820, 0.933> }
			
			}
			
			//----- ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null001 -----
			object { ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null001_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null014 -----
			object { ${REFERENCE}_C_0805_2012Metric_null014_mesh
			}
			
			//----- ${REFERENCE}_CP_Elec_18x175_null001 -----
			object { ${REFERENCE}_CP_Elec_18x175_null001_mesh
			}
			
			//----- ${REFERENCE}_DC044_connector_5_5x2_1mm_null -----
			object { ${REFERENCE}_DC044_connector_5_5x2_1mm_null_mesh
					pigment { color rgb <0.506, 0.506, 0.506> }
			
			}
			
			//----- ${REFERENCE}_SW_SPST_TL3301_6x6mm_H4_3mm_null001 -----
			object { ${REFERENCE}_SW_SPST_TL3301_6x6mm_H4_3mm_null001_mesh
					pigment { color rgb <0.388, 0.310, 0.129> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null015 -----
			object { ${REFERENCE}_R_0805_2012Metric_null015_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null015 -----
			object { ${REFERENCE}_C_0805_2012Metric_null015_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null016 -----
			object { ${REFERENCE}_R_0805_2012Metric_null016_mesh
			}
			
			//----- ${REFERENCE}_D_SMA_null -----
			object { ${REFERENCE}_D_SMA_null_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null017 -----
			object { ${REFERENCE}_R_0805_2012Metric_null017_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null016 -----
			object { ${REFERENCE}_C_0805_2012Metric_null016_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null017 -----
			object { ${REFERENCE}_C_0805_2012Metric_null017_mesh
			}
			
			//----- ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null002 -----
			object { ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null002_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null018 -----
			object { ${REFERENCE}_C_0805_2012Metric_null018_mesh
			}
			
			//----- ${REFERENCE}_Inductor_Coilcraft_0805CS_null -----
			object { ${REFERENCE}_Inductor_Coilcraft_0805CS_null_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null018 -----
			object { ${REFERENCE}_R_0805_2012Metric_null018_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null019 -----
			object { ${REFERENCE}_C_0805_2012Metric_null019_mesh
			}
			
			//----- ${REFERENCE}_PinHeader_1x06_P127mm_Vertical_null -----
			object { ${REFERENCE}_PinHeader_1x06_P127mm_Vertical_null_mesh
			}
			
			//----- ${REFERENCE}_Fuse_MXT250_With_Socket_null -----
			object { ${REFERENCE}_Fuse_MXT250_With_Socket_null_mesh
					pigment { color rgb <0.898, 0.898, 0.898> }
			
			}
			
			//----- ${REFERENCE}_Fuse_MXT250_null[2] -----
			object { ${REFERENCE}_Fuse_MXT250_null[2]_mesh
					pigment { color rgb <0.898, 0.898, 0.898> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null020 -----
			object { ${REFERENCE}_C_0805_2012Metric_null020_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null019 -----
			object { ${REFERENCE}_R_0805_2012Metric_null019_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null020 -----
			object { ${REFERENCE}_R_0805_2012Metric_null020_mesh
			}
			
			//----- ${REFERENCE}_PE5393NSL_inductor_null -----
			object { ${REFERENCE}_PE5393NSL_inductor_null_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null021 -----
			object { ${REFERENCE}_C_0805_2012Metric_null021_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null022 -----
			object { ${REFERENCE}_C_0805_2012Metric_null022_mesh
			}
			
			//----- ${REFERENCE}_CP_Elec_18x175_null002 -----
			object { ${REFERENCE}_CP_Elec_18x175_null002_mesh
			}
			
			//----- ${REFERENCE}_MAX6952EAX__null -----
			object { ${REFERENCE}_MAX6952EAX__null_mesh
					pigment { color rgb <0.302, 0.302, 0.302> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null021 -----
			object { ${REFERENCE}_R_0805_2012Metric_null021_mesh
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null022 -----
			object { ${REFERENCE}_R_0805_2012Metric_null022_mesh
			}
			
			//----- ${REFERENCE}_PogoFemale_null -----
			object { ${REFERENCE}_PogoFemale_null_mesh
					pigment { color rgb <0.953, 0.796, 0.486> }
			
			}
			
			//----- ${REFERENCE}_R_0805_2012Metric_null023 -----
			object { ${REFERENCE}_R_0805_2012Metric_null023_mesh
			}
			
			//----- ${REFERENCE}_LM2596DSADJR4G_null -----
			object { ${REFERENCE}_LM2596DSADJR4G_null_mesh
					pigment { color rgb <0.792, 0.820, 0.933> }
			
			}
			
			//----- ${REFERENCE}_MAX6952EAX__null001 -----
			object { ${REFERENCE}_MAX6952EAX__null001_mesh
					pigment { color rgb <0.302, 0.302, 0.302> }
			
			}
			
			//----- ${REFERENCE}_Ublox_LEA_M8T_null -----
			object { ${REFERENCE}_Ublox_LEA_M8T_null_mesh
					pigment { color rgb <0.302, 0.302, 0.302> }
			
			}
			
			//----- ${REFERENCE}_SOT_223_null002 -----
			object { ${REFERENCE}_SOT_223_null002_mesh
			}
			
			//----- ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null003 -----
			object { ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null003_mesh
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null023 -----
			object { ${REFERENCE}_C_0805_2012Metric_null023_mesh
			}
			
			//----- ${REFERENCE}_CP_Elec_8x10_null -----
			object { ${REFERENCE}_CP_Elec_8x10_null_mesh
			}
			
			//----- ${REFERENCE}_TP094003_Transducer_9x9mm_null -----
			object { ${REFERENCE}_TP094003_Transducer_9x9mm_null_mesh
					pigment { color rgb <0.400, 0.275, 0.000> }
			
			}
			
			//----- ${REFERENCE}_C_0805_2012Metric_null024 -----
			object { ${REFERENCE}_C_0805_2012Metric_null024_mesh
			}
			
			//----- ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null004 -----
			object { ${REFERENCE}_HTSSOP_28_1EP_44x97mm_P065mm_null004_mesh
			}
			
			//----- ${REFERENCE}_CMS04_null -----
			object { ${REFERENCE}_CMS04_null_mesh
					pigment { color rgb <0.733, 0.773, 0.796> }
			
			}
			
			//----- ${REFERENCE}_SOT_223_null003 -----
			object { ${REFERENCE}_SOT_223_null003_mesh
			}
			
		}
		
	}
	
	translate <0.0, 0.0, 28.2>
}

//----- X_Axis001 -----
//----- Y_Axis001 -----
//----- Z_Axis001 -----
//----- XY_Plane001 -----
//----- XZ_Plane001 -----
//----- Board_7182 -----
//----- X_Axis002 -----
//----- Y_Axis002 -----
//----- Z_Axis002 -----
//----- XY_Plane002 -----
//----- XZ_Plane002 -----
//----- Step_Models_7182 -----
//----- X_Axis003 -----
//----- Y_Axis003 -----
//----- Z_Axis003 -----
//----- XY_Plane003 -----
//----- XZ_Plane003 -----
//----- Top_7182 -----
//----- X_Axis004 -----
//----- Y_Axis004 -----
//----- Z_Axis004 -----
//----- XY_Plane004 -----
//----- XZ_Plane004 -----
//----- Bot_7182 -----
//----- back_plate -----
union {

	//----- Pocket002 -----
	difference {
	
		//----- Pocket001 -----
		difference {
		
			//----- Pocket -----
			difference {
			
				//----- Pad___Aluminum_plate -----
				union {
				
					prism {
						bezier_spline
						0, -1.6, 16
						<5.334, -5.334>, <5.334, -5.334>, <-244.856, -5.334>, <-244.856, -5.334>//line
						<-244.856, -5.334>, <-244.856, -5.334>, <-244.856, 244.856>, <-244.856, 244.856>//line
						<-244.856, 244.856>, <-244.856, 244.856>, <5.334, 244.856>, <5.334, 244.856>//line
						<5.334, 244.856>, <5.334, 244.856>, <5.334, -5.334>, <5.334, -5.334>//line
						
						rotate <-90.0, 0.0, 180.0>
				
					}
				
				}
				
				prism {
					bezier_spline
					0.0001, -5.0, 64
					<47.956, -41.27>, <47.956, -41.27>, <47.024, -46.51>, <47.024, -46.51>//line
					<47.024, -46.51>, <45.24, -48.08>, <44.614, -50.590999999999994>, <45.452, -52.815>//arc
					<45.452, -52.815>, <46.29, -55.039>, <48.416999999999994, -56.513>, <50.794, -56.515>//arc
					<50.794, -56.515>, <53.171, -56.517>, <55.302, -55.049>, <56.144, -52.826>//arc
					<56.144, -52.826>, <56.986, -50.603>, <56.365, -48.091>, <54.584, -46.517>//arc
					<54.584, -46.517>, <54.584, -46.517>, <53.666, -41.277>, <53.666, -41.277>//line
					<53.666, -41.277>, <53.321999999999996, -39.983000000000004>, <52.152, -39.083000000000006>, <50.814, -39.081>//arc
					<50.814, -39.081>, <49.476, -39.079>, <48.303000000000004, -39.977000000000004>, <47.956, -41.27>//arc
					<185.844, -41.35>, <185.844, -41.35>, <184.944, -46.51>, <184.944, -46.51>//line
					<184.944, -46.51>, <183.16, -48.08>, <182.53400000000002, -50.590999999999994>, <183.372, -52.815>//arc
					<183.372, -52.815>, <184.21, -55.039>, <186.337, -56.513>, <188.714, -56.515>//arc
					<188.714, -56.515>, <191.091, -56.517>, <193.22199999999998, -55.049>, <194.064, -52.826>//arc
					<194.064, -52.826>, <194.906, -50.603>, <194.285, -48.091>, <192.504, -46.517>//arc
					<192.504, -46.517>, <192.504, -46.517>, <191.574, -41.265>, <191.574, -41.265>//line
					<191.574, -41.265>, <191.22400000000002, -39.957>, <190.03, -39.055>, <188.676, -39.075>//arc
					<188.676, -39.075>, <187.32199999999997, -39.095000000000006>, <186.156, -40.033>, <185.844, -41.35>//arc
					
					rotate <-90.0, 0.0, 0.0>
			
				}
			
			}
			
			prism {
				bezier_spline
				0.0001, -5.0, 64
				<217.17, -214.885>, <218.432, -214.885>, <219.45499999999998, -215.908>, <219.45499999999998, -217.17>//circle
				<219.45499999999998, -217.17>, <219.45499999999998, -218.432>, <218.432, -219.45499999999998>, <217.17, -219.45499999999998>//circle
				<217.17, -219.45499999999998>, <215.908, -219.45499999999998>, <214.885, -218.432>, <214.885, -217.17>//circle
				<214.885, -217.17>, <214.885, -215.908>, <215.908, -214.885>, <217.17, -214.885>//circle
				<22.35, -214.885>, <23.612000000000002, -214.885>, <24.635, -215.908>, <24.635, -217.17>//circle
				<24.635, -217.17>, <24.635, -218.432>, <23.612000000000002, -219.45499999999998>, <22.35, -219.45499999999998>//circle
				<22.35, -219.45499999999998>, <21.088, -219.45499999999998>, <20.065, -218.432>, <20.065, -217.17>//circle
				<20.065, -217.17>, <20.065, -215.908>, <21.088, -214.885>, <22.35, -214.885>//circle
				<217.17, -20.065>, <218.432, -20.065>, <219.45499999999998, -21.088>, <219.45499999999998, -22.35>//circle
				<219.45499999999998, -22.35>, <219.45499999999998, -23.612000000000002>, <218.432, -24.635>, <217.17, -24.635>//circle
				<217.17, -24.635>, <215.908, -24.635>, <214.885, -23.612000000000002>, <214.885, -22.35>//circle
				<214.885, -22.35>, <214.885, -21.088>, <215.908, -20.065>, <217.17, -20.065>//circle
				<22.35, -20.065>, <23.612000000000002, -20.065>, <24.635, -21.088>, <24.635, -22.35>//circle
				<24.635, -22.35>, <24.635, -23.612000000000002>, <23.612000000000002, -24.635>, <22.35, -24.635>//circle
				<22.35, -24.635>, <21.088, -24.635>, <20.065, -23.612000000000002>, <20.065, -22.35>//circle
				<20.065, -22.35>, <20.065, -21.088>, <21.088, -20.065>, <22.35, -20.065>//circle
				
				rotate <-90.0, 0.0, 0.0>
		
			}
		
		}
		
		prism {
			bezier_spline
			0.0001, -5.0, 144
			<4.826, -3.3019999999999996>, <5.667999999999999, -3.3019999999999996>, <6.35, -3.9839999999999995>, <6.35, -4.826>//circle
			<6.35, -4.826>, <6.35, -5.667999999999999>, <5.667999999999999, -6.35>, <4.826, -6.35>//circle
			<4.826, -6.35>, <3.9839999999999995, -6.35>, <3.3019999999999996, -5.667999999999999>, <3.3019999999999996, -4.826>//circle
			<3.3019999999999996, -4.826>, <3.3019999999999996, -3.9839999999999995>, <3.9839999999999995, -3.3019999999999996>, <4.826, -3.3019999999999996>//circle
			<234.696, -3.3019999999999987>, <235.538, -3.3019999999999987>, <236.22, -3.9839999999999995>, <236.22, -4.826>//circle
			<236.22, -4.826>, <236.22, -5.667999999999999>, <235.538, -6.3500000000000005>, <234.696, -6.3500000000000005>//circle
			<234.696, -6.3500000000000005>, <233.85399999999998, -6.3500000000000005>, <233.172, -5.667999999999999>, <233.172, -4.826>//circle
			<233.172, -4.826>, <233.172, -3.9839999999999995>, <233.85399999999998, -3.3019999999999987>, <234.696, -3.3019999999999987>//circle
			<4.826, -233.172>, <5.667999999999999, -233.172>, <6.35, -233.85399999999998>, <6.35, -234.696>//circle
			<6.35, -234.696>, <6.35, -235.538>, <5.667999999999999, -236.22>, <4.826, -236.22>//circle
			<4.826, -236.22>, <3.9839999999999995, -236.22>, <3.3019999999999996, -235.538>, <3.3019999999999996, -234.696>//circle
			<3.3019999999999996, -234.696>, <3.3019999999999996, -233.85399999999998>, <3.9839999999999995, -233.172>, <4.826, -233.172>//circle
			<234.696, -233.172>, <235.538, -233.172>, <236.22, -233.85399999999998>, <236.22, -234.696>//circle
			<236.22, -234.696>, <236.22, -235.538>, <235.538, -236.22>, <234.696, -236.22>//circle
			<234.696, -236.22>, <233.85399999999998, -236.22>, <233.172, -235.538>, <233.172, -234.696>//circle
			<233.172, -234.696>, <233.172, -233.85399999999998>, <233.85399999999998, -233.172>, <234.696, -233.172>//circle
			<4.826, -118.237>, <5.667999999999999, -118.237>, <6.35, -118.919>, <6.35, -119.761>//circle
			<6.35, -119.761>, <6.35, -120.603>, <5.667999999999999, -121.285>, <4.826, -121.285>//circle
			<4.826, -121.285>, <3.9839999999999995, -121.285>, <3.3019999999999996, -120.603>, <3.3019999999999996, -119.761>//circle
			<3.3019999999999996, -119.761>, <3.3019999999999996, -118.919>, <3.9839999999999995, -118.237>, <4.826, -118.237>//circle
			<119.761, -118.237>, <120.603, -118.237>, <121.285, -118.919>, <121.285, -119.761>//circle
			<121.285, -119.761>, <121.285, -120.603>, <120.603, -121.285>, <119.761, -121.285>//circle
			<119.761, -121.285>, <118.919, -121.285>, <118.237, -120.603>, <118.237, -119.761>//circle
			<118.237, -119.761>, <118.237, -118.919>, <118.919, -118.237>, <119.761, -118.237>//circle
			<234.696, -118.237>, <235.538, -118.237>, <236.22, -118.919>, <236.22, -119.761>//circle
			<236.22, -119.761>, <236.22, -120.603>, <235.538, -121.285>, <234.696, -121.285>//circle
			<234.696, -121.285>, <233.85399999999998, -121.285>, <233.172, -120.603>, <233.172, -119.761>//circle
			<233.172, -119.761>, <233.172, -118.919>, <233.85399999999998, -118.237>, <234.696, -118.237>//circle
			<119.761, -233.172>, <120.603, -233.172>, <121.285, -233.85399999999998>, <121.285, -234.696>//circle
			<121.285, -234.696>, <121.285, -235.538>, <120.603, -236.22>, <119.761, -236.22>//circle
			<119.761, -236.22>, <118.919, -236.22>, <118.237, -235.538>, <118.237, -234.696>//circle
			<118.237, -234.696>, <118.237, -233.85399999999998>, <118.919, -233.172>, <119.761, -233.172>//circle
			<119.761, -3.3019999999999987>, <120.603, -3.3019999999999987>, <121.285, -3.9839999999999995>, <121.285, -4.826>//circle
			<121.285, -4.826>, <121.285, -5.667999999999999>, <120.603, -6.3500000000000005>, <119.761, -6.3500000000000005>//circle
			<119.761, -6.3500000000000005>, <118.919, -6.3500000000000005>, <118.237, -5.667999999999999>, <118.237, -4.826>//circle
			<118.237, -4.826>, <118.237, -3.9839999999999995>, <118.919, -3.3019999999999987>, <119.761, -3.3019999999999987>//circle
			
			rotate <-90.0, 0.0, 0.0>
	
		}
	
	}
	
}

//----- X_Axis005 -----
//----- Y_Axis005 -----
//----- Z_Axis005 -----
//----- XY_Plane005 -----
//----- XZ_Plane005 -----
//----- YZ_Plane005 -----
//----- Standoff_upper_left -----
union {

	//----- SOLID -----
	object { SOLID_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND -----
	translate <4.82, -4.82, 1.6>
}

//----- X_Axis006 -----
//----- Y_Axis006 -----
//----- Z_Axis006 -----
//----- XY_Plane006 -----
//----- XZ_Plane006 -----
//----- YZ_Plane006 -----
//----- XY_Plane007 -----
//----- XZ_Plane007 -----
//----- X_Axis007 -----
//----- YZ_Plane007 -----
//----- Y_Axis007 -----
//----- Z_Axis007 -----
//----- Standoff_middle_left -----
union {

	//----- SOLID001 -----
	object { SOLID001_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND001 -----
	translate <4.82, -119.77, 1.6>
}

//----- XY_Plane008 -----
//----- XZ_Plane008 -----
//----- X_Axis008 -----
//----- YZ_Plane008 -----
//----- Y_Axis008 -----
//----- Z_Axis008 -----
//----- Standoff_bottom_left -----
union {

	//----- SOLID002 -----
	object { SOLID002_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND002 -----
	translate <4.82, -234.7, 1.6>
}

//----- XY_Plane009 -----
//----- XZ_Plane009 -----
//----- X_Axis009 -----
//----- YZ_Plane009 -----
//----- Y_Axis009 -----
//----- Z_Axis009 -----
//----- Standoff_bottom_right -----
union {

	//----- SOLID003 -----
	object { SOLID003_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND003 -----
	translate <234.7, -234.7, 1.6>
}

//----- XY_Plane010 -----
//----- XZ_Plane010 -----
//----- X_Axis010 -----
//----- YZ_Plane010 -----
//----- Y_Axis010 -----
//----- Z_Axis010 -----
//----- Standoff_middle_right -----
union {

	//----- SOLID004 -----
	object { SOLID004_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND004 -----
	translate <234.7, -119.77, 1.6>
}

//----- XY_Plane011 -----
//----- XZ_Plane011 -----
//----- X_Axis011 -----
//----- YZ_Plane011 -----
//----- Y_Axis011 -----
//----- Z_Axis011 -----
//----- Standoff_upper_right -----
union {

	//----- SOLID005 -----
	object { SOLID005_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND005 -----
	translate <234.7, -4.82, 1.6>
}

//----- XY_Plane012 -----
//----- XZ_Plane012 -----
//----- X_Axis012 -----
//----- YZ_Plane012 -----
//----- Y_Axis012 -----
//----- Z_Axis012 -----
//----- Standoff_upper_middle -----
union {

	//----- SOLID006 -----
	object { SOLID006_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND006 -----
	translate <119.77, -4.82, 1.6>
}

//----- XY_Plane013 -----
//----- XZ_Plane013 -----
//----- X_Axis013 -----
//----- YZ_Plane013 -----
//----- Y_Axis013 -----
//----- Z_Axis013 -----
//----- Standoff_centre -----
union {

	//----- SOLID007 -----
	object { SOLID007_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND007 -----
	translate <119.77, -119.77, 1.6>
}

//----- XY_Plane014 -----
//----- XZ_Plane014 -----
//----- X_Axis014 -----
//----- YZ_Plane014 -----
//----- Y_Axis014 -----
//----- Z_Axis014 -----
//----- Standoff_bottom_middle -----
union {

	//----- SOLID008 -----
	object { SOLID008_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND008 -----
	translate <119.77, -234.7, 1.6>
}

//----- Standoff_frontpanel_upper_left -----
union {

	//----- SOLID009 -----
	object { SOLID009_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND009 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <4.82, -4.82, 33.2>
}

//----- X_Axis015 -----
//----- Y_Axis015 -----
//----- Z_Axis015 -----
//----- XY_Plane015 -----
//----- XZ_Plane015 -----
//----- YZ_Plane015 -----
//----- XY_Plane016 -----
//----- XZ_Plane016 -----
//----- X_Axis016 -----
//----- YZ_Plane016 -----
//----- Y_Axis016 -----
//----- Z_Axis016 -----
//----- Standoff_frontpanel_middle_left -----
union {

	//----- SOLID010 -----
	object { SOLID010_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND010 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <4.82, -119.77, 33.2>
}

//----- XY_Plane017 -----
//----- XZ_Plane017 -----
//----- X_Axis017 -----
//----- YZ_Plane017 -----
//----- Y_Axis017 -----
//----- Z_Axis017 -----
//----- Standoff_frontpanel_bottom_left -----
union {

	//----- SOLID011 -----
	object { SOLID011_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND011 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <4.82, -234.7, 33.2>
}

//----- XY_Plane018 -----
//----- XZ_Plane018 -----
//----- X_Axis018 -----
//----- YZ_Plane018 -----
//----- Y_Axis018 -----
//----- Z_Axis018 -----
//----- Standoff_frontpanel_bottom_middle -----
union {

	//----- SOLID012 -----
	object { SOLID012_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND012 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <119.77, -234.7, 33.2>
}

//----- XY_Plane019 -----
//----- XZ_Plane019 -----
//----- X_Axis019 -----
//----- YZ_Plane019 -----
//----- Y_Axis019 -----
//----- Z_Axis019 -----
//----- Standoff_frontpanel_bottom_right -----
union {

	//----- SOLID013 -----
	object { SOLID013_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND013 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <234.7, -234.7, 33.2>
}

//----- XY_Plane020 -----
//----- XZ_Plane020 -----
//----- X_Axis020 -----
//----- YZ_Plane020 -----
//----- Y_Axis020 -----
//----- Z_Axis020 -----
//----- Standoff_frontpanel_centre -----
union {

	//----- SOLID014 -----
	object { SOLID014_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND014 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <119.77, -119.77, 33.2>
}

//----- XY_Plane021 -----
//----- XZ_Plane021 -----
//----- X_Axis021 -----
//----- YZ_Plane021 -----
//----- Y_Axis021 -----
//----- Z_Axis021 -----
//----- Standoff_frontpanel_upper_middle -----
union {

	//----- SOLID015 -----
	object { SOLID015_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND015 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <119.77, -4.82, 33.2>
}

//----- XY_Plane022 -----
//----- XZ_Plane022 -----
//----- X_Axis022 -----
//----- YZ_Plane022 -----
//----- Y_Axis022 -----
//----- Z_Axis022 -----
//----- Standoff_frontpanel_middle_right -----
union {

	//----- SOLID016 -----
	object { SOLID016_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND016 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <234.7, -119.77, 33.2>
}

//----- XY_Plane023 -----
//----- XZ_Plane023 -----
//----- X_Axis023 -----
//----- YZ_Plane023 -----
//----- Y_Axis023 -----
//----- Z_Axis023 -----
//----- Standoff_frontpanel_upper_right -----
union {

	//----- SOLID017 -----
	object { SOLID017_mesh
			pigment { color rgb <0.565, 0.565, 0.565> }
	
	}
	
	//----- COMPOUND017 -----
	rotate <180.0, 7.016709298534876e-15, 180.0>
	translate <234.7, -4.82, 33.2>
}

//----- front_panel -----
union {

	//----- Pocket004 -----
	difference {
	
		//----- Pocket003 -----
		difference {
		
			//----- Pad001 -----
			union {
			
				prism {
					bezier_spline
					0, -3.0, 16
					<0.0, -239.522>, <0.0, -239.522>, <0.0, 0.0>, <0.0, 0.0>//line
					<0.0, 0.0>, <0.0, 0.0>, <239.522, 0.0>, <239.522, 0.0>//line
					<239.522, 0.0>, <239.522, 0.0>, <239.522, -239.522>, <239.522, -239.522>//line
					<239.522, -239.522>, <239.522, -239.522>, <0.0, -239.522>, <0.0, -239.522>//line
					
					rotate <-90.0, 0.0, 0.0>
			
				}
			
			}
			
			prism {
				bezier_spline
				0.0001, -5.0, 5680
				<119.761, -90.44305>, <120.312, -90.44305>, <120.75795, -90.889>, <120.75795, -91.44>//circle
				<120.75795, -91.44>, <120.75795, -91.991>, <120.312, -92.43695>, <119.761, -92.43695>//circle
				<119.761, -92.43695>, <119.21, -92.43695>, <118.76405, -91.991>, <118.76405, -91.44>//circle
				<118.76405, -91.44>, <118.76405, -90.889>, <119.21, -90.44305>, <119.761, -90.44305>//circle
				<116.205, -189.2935>, <117.082, -189.2935>, <117.7925, -190.004>, <117.7925, -190.881>//circle
				<117.7925, -190.881>, <117.7925, -191.758>, <117.082, -192.4685>, <116.205, -192.4685>//circle
				<116.205, -192.4685>, <115.328, -192.4685>, <114.61749999999999, -191.758>, <114.61749999999999, -190.881>//circle
				<114.61749999999999, -190.881>, <114.61749999999999, -190.004>, <115.328, -189.2935>, <116.205, -189.2935>//circle
				<116.205, -77.53349999999999>, <117.082, -77.53349999999999>, <117.7925, -78.244>, <117.7925, -79.121>//circle
				<117.7925, -79.121>, <117.7925, -79.99799999999999>, <117.082, -80.7085>, <116.205, -80.7085>//circle
				<116.205, -80.7085>, <115.328, -80.7085>, <114.61749999999999, -79.99799999999999>, <114.61749999999999, -79.121>//circle
				<114.61749999999999, -79.121>, <114.61749999999999, -78.244>, <115.328, -77.53349999999999>, <116.205, -77.53349999999999>//circle
				<143.637, -189.2935>, <144.514, -189.2935>, <145.2245, -190.004>, <145.2245, -190.881>//circle
				<145.2245, -190.881>, <145.2245, -191.758>, <144.514, -192.4685>, <143.637, -192.4685>//circle
				<143.637, -192.4685>, <142.76, -192.4685>, <142.0495, -191.758>, <142.0495, -190.881>//circle
				<142.0495, -190.881>, <142.0495, -190.004>, <142.76, -189.2935>, <143.637, -189.2935>//circle
				<143.637, -77.53349999999999>, <144.514, -77.53349999999999>, <145.2245, -78.244>, <145.2245, -79.121>//circle
				<145.2245, -79.121>, <145.2245, -79.99799999999999>, <144.514, -80.7085>, <143.637, -80.7085>//circle
				<143.637, -80.7085>, <142.76, -80.7085>, <142.0495, -79.99799999999999>, <142.0495, -79.121>//circle
				<142.0495, -79.121>, <142.0495, -78.244>, <142.76, -77.53349999999999>, <143.637, -77.53349999999999>//circle
				<111.125, -189.2935>, <112.002, -189.2935>, <112.7125, -190.004>, <112.7125, -190.881>//circle
				<112.7125, -190.881>, <112.7125, -191.758>, <112.002, -192.4685>, <111.125, -192.4685>//circle
				<111.125, -192.4685>, <110.248, -192.4685>, <109.5375, -191.758>, <109.5375, -190.881>//circle
				<109.5375, -190.881>, <109.5375, -190.004>, <110.248, -189.2935>, <111.125, -189.2935>//circle
				<111.125, -77.53349999999999>, <112.002, -77.53349999999999>, <112.7125, -78.244>, <112.7125, -79.121>//circle
				<112.7125, -79.121>, <112.7125, -79.99799999999999>, <112.002, -80.7085>, <111.125, -80.7085>//circle
				<111.125, -80.7085>, <110.248, -80.7085>, <109.5375, -79.99799999999999>, <109.5375, -79.121>//circle
				<109.5375, -79.121>, <109.5375, -78.244>, <110.248, -77.53349999999999>, <111.125, -77.53349999999999>//circle
				<138.557, -189.2935>, <139.434, -189.2935>, <140.1445, -190.004>, <140.1445, -190.881>//circle
				<140.1445, -190.881>, <140.1445, -191.758>, <139.434, -192.4685>, <138.557, -192.4685>//circle
				<138.557, -192.4685>, <137.67999999999998, -192.4685>, <136.96949999999998, -191.758>, <136.96949999999998, -190.881>//circle
				<136.96949999999998, -190.881>, <136.96949999999998, -190.004>, <137.67999999999998, -189.2935>, <138.557, -189.2935>//circle
				<138.557, -77.53349999999999>, <139.434, -77.53349999999999>, <140.1445, -78.244>, <140.1445, -79.121>//circle
				<140.1445, -79.121>, <140.1445, -79.99799999999999>, <139.434, -80.7085>, <138.557, -80.7085>//circle
				<138.557, -80.7085>, <137.67999999999998, -80.7085>, <136.96949999999998, -79.99799999999999>, <136.96949999999998, -79.121>//circle
				<136.96949999999998, -79.121>, <136.96949999999998, -78.244>, <137.67999999999998, -77.53349999999999>, <138.557, -77.53349999999999>//circle
				<106.045, -189.2935>, <106.922, -189.2935>, <107.63250000000001, -190.004>, <107.63250000000001, -190.881>//circle
				<107.63250000000001, -190.881>, <107.63250000000001, -191.758>, <106.922, -192.4685>, <106.045, -192.4685>//circle
				<106.045, -192.4685>, <105.168, -192.4685>, <104.4575, -191.758>, <104.4575, -190.881>//circle
				<104.4575, -190.881>, <104.4575, -190.004>, <105.168, -189.2935>, <106.045, -189.2935>//circle
				<106.045, -77.53349999999999>, <106.922, -77.53349999999999>, <107.63250000000001, -78.244>, <107.63250000000001, -79.121>//circle
				<107.63250000000001, -79.121>, <107.63250000000001, -79.99799999999999>, <106.922, -80.7085>, <106.045, -80.7085>//circle
				<106.045, -80.7085>, <105.168, -80.7085>, <104.4575, -79.99799999999999>, <104.4575, -79.121>//circle
				<104.4575, -79.121>, <104.4575, -78.244>, <105.168, -77.53349999999999>, <106.045, -77.53349999999999>//circle
				<133.477, -189.2935>, <134.354, -189.2935>, <135.0645, -190.004>, <135.0645, -190.881>//circle
				<135.0645, -190.881>, <135.0645, -191.758>, <134.354, -192.4685>, <133.477, -192.4685>//circle
				<133.477, -192.4685>, <132.6, -192.4685>, <131.8895, -191.758>, <131.8895, -190.881>//circle
				<131.8895, -190.881>, <131.8895, -190.004>, <132.6, -189.2935>, <133.477, -189.2935>//circle
				<133.477, -77.53349999999999>, <134.354, -77.53349999999999>, <135.0645, -78.244>, <135.0645, -79.121>//circle
				<135.0645, -79.121>, <135.0645, -79.99799999999999>, <134.354, -80.7085>, <133.477, -80.7085>//circle
				<133.477, -80.7085>, <132.6, -80.7085>, <131.8895, -79.99799999999999>, <131.8895, -79.121>//circle
				<131.8895, -79.121>, <131.8895, -78.244>, <132.6, -77.53349999999999>, <133.477, -77.53349999999999>//circle
				<100.965, -189.2935>, <101.842, -189.2935>, <102.55250000000001, -190.004>, <102.55250000000001, -190.881>//circle
				<102.55250000000001, -190.881>, <102.55250000000001, -191.758>, <101.842, -192.4685>, <100.965, -192.4685>//circle
				<100.965, -192.4685>, <100.08800000000001, -192.4685>, <99.3775, -191.758>, <99.3775, -190.881>//circle
				<99.3775, -190.881>, <99.3775, -190.004>, <100.08800000000001, -189.2935>, <100.965, -189.2935>//circle
				<100.965, -77.53349999999999>, <101.842, -77.53349999999999>, <102.55250000000001, -78.244>, <102.55250000000001, -79.121>//circle
				<102.55250000000001, -79.121>, <102.55250000000001, -79.99799999999999>, <101.842, -80.7085>, <100.965, -80.7085>//circle
				<100.965, -80.7085>, <100.08800000000001, -80.7085>, <99.3775, -79.99799999999999>, <99.3775, -79.121>//circle
				<99.3775, -79.121>, <99.3775, -78.244>, <100.08800000000001, -77.53349999999999>, <100.965, -77.53349999999999>//circle
				<128.397, -189.2935>, <129.274, -189.2935>, <129.9845, -190.004>, <129.9845, -190.881>//circle
				<129.9845, -190.881>, <129.9845, -191.758>, <129.274, -192.4685>, <128.397, -192.4685>//circle
				<128.397, -192.4685>, <127.52, -192.4685>, <126.80949999999999, -191.758>, <126.80949999999999, -190.881>//circle
				<126.80949999999999, -190.881>, <126.80949999999999, -190.004>, <127.52, -189.2935>, <128.397, -189.2935>//circle
				<128.397, -77.53349999999999>, <129.274, -77.53349999999999>, <129.9845, -78.244>, <129.9845, -79.121>//circle
				<129.9845, -79.121>, <129.9845, -79.99799999999999>, <129.274, -80.7085>, <128.397, -80.7085>//circle
				<128.397, -80.7085>, <127.52, -80.7085>, <126.80949999999999, -79.99799999999999>, <126.80949999999999, -79.121>//circle
				<126.80949999999999, -79.121>, <126.80949999999999, -78.244>, <127.52, -77.53349999999999>, <128.397, -77.53349999999999>//circle
				<95.885, -189.2935>, <96.762, -189.2935>, <97.47250000000001, -190.004>, <97.47250000000001, -190.881>//circle
				<97.47250000000001, -190.881>, <97.47250000000001, -191.758>, <96.762, -192.4685>, <95.885, -192.4685>//circle
				<95.885, -192.4685>, <95.00800000000001, -192.4685>, <94.2975, -191.758>, <94.2975, -190.881>//circle
				<94.2975, -190.881>, <94.2975, -190.004>, <95.00800000000001, -189.2935>, <95.885, -189.2935>//circle
				<95.885, -77.53349999999999>, <96.762, -77.53349999999999>, <97.47250000000001, -78.244>, <97.47250000000001, -79.121>//circle
				<97.47250000000001, -79.121>, <97.47250000000001, -79.99799999999999>, <96.762, -80.7085>, <95.885, -80.7085>//circle
				<95.885, -80.7085>, <95.00800000000001, -80.7085>, <94.2975, -79.99799999999999>, <94.2975, -79.121>//circle
				<94.2975, -79.121>, <94.2975, -78.244>, <95.00800000000001, -77.53349999999999>, <95.885, -77.53349999999999>//circle
				<123.317, -189.2935>, <124.19399999999999, -189.2935>, <124.9045, -190.004>, <124.9045, -190.881>//circle
				<124.9045, -190.881>, <124.9045, -191.758>, <124.19399999999999, -192.4685>, <123.317, -192.4685>//circle
				<123.317, -192.4685>, <122.44, -192.4685>, <121.72949999999999, -191.758>, <121.72949999999999, -190.881>//circle
				<121.72949999999999, -190.881>, <121.72949999999999, -190.004>, <122.44, -189.2935>, <123.317, -189.2935>//circle
				<123.317, -77.53349999999999>, <124.19399999999999, -77.53349999999999>, <124.9045, -78.244>, <124.9045, -79.121>//circle
				<124.9045, -79.121>, <124.9045, -79.99799999999999>, <124.19399999999999, -80.7085>, <123.317, -80.7085>//circle
				<123.317, -80.7085>, <122.44, -80.7085>, <121.72949999999999, -79.99799999999999>, <121.72949999999999, -79.121>//circle
				<121.72949999999999, -79.121>, <121.72949999999999, -78.244>, <122.44, -77.53349999999999>, <123.317, -77.53349999999999>//circle
				<95.885, -184.21349999999998>, <96.762, -184.21349999999998>, <97.47250000000001, -184.92399999999998>, <97.47250000000001, -185.801>//circle
				<97.47250000000001, -185.801>, <97.47250000000001, -186.678>, <96.762, -187.3885>, <95.885, -187.3885>//circle
				<95.885, -187.3885>, <95.00800000000001, -187.3885>, <94.2975, -186.678>, <94.2975, -185.801>//circle
				<94.2975, -185.801>, <94.2975, -184.92399999999998>, <95.00800000000001, -184.21349999999998>, <95.885, -184.21349999999998>//circle
				<95.885, -72.45349999999999>, <96.762, -72.45349999999999>, <97.47250000000001, -73.164>, <97.47250000000001, -74.041>//circle
				<97.47250000000001, -74.041>, <97.47250000000001, -74.91799999999999>, <96.762, -75.6285>, <95.885, -75.6285>//circle
				<95.885, -75.6285>, <95.00800000000001, -75.6285>, <94.2975, -74.91799999999999>, <94.2975, -74.041>//circle
				<94.2975, -74.041>, <94.2975, -73.164>, <95.00800000000001, -72.45349999999999>, <95.885, -72.45349999999999>//circle
				<123.317, -184.21349999999998>, <124.19399999999999, -184.21349999999998>, <124.9045, -184.92399999999998>, <124.9045, -185.801>//circle
				<124.9045, -185.801>, <124.9045, -186.678>, <124.19399999999999, -187.3885>, <123.317, -187.3885>//circle
				<123.317, -187.3885>, <122.44, -187.3885>, <121.72949999999999, -186.678>, <121.72949999999999, -185.801>//circle
				<121.72949999999999, -185.801>, <121.72949999999999, -184.92399999999998>, <122.44, -184.21349999999998>, <123.317, -184.21349999999998>//circle
				<123.317, -72.45349999999999>, <124.19399999999999, -72.45349999999999>, <124.9045, -73.164>, <124.9045, -74.041>//circle
				<124.9045, -74.041>, <124.9045, -74.91799999999999>, <124.19399999999999, -75.6285>, <123.317, -75.6285>//circle
				<123.317, -75.6285>, <122.44, -75.6285>, <121.72949999999999, -74.91799999999999>, <121.72949999999999, -74.041>//circle
				<121.72949999999999, -74.041>, <121.72949999999999, -73.164>, <122.44, -72.45349999999999>, <123.317, -72.45349999999999>//circle
				<95.885, -179.1335>, <96.762, -179.1335>, <97.47250000000001, -179.844>, <97.47250000000001, -180.721>//circle
				<97.47250000000001, -180.721>, <97.47250000000001, -181.598>, <96.762, -182.3085>, <95.885, -182.3085>//circle
				<95.885, -182.3085>, <95.00800000000001, -182.3085>, <94.2975, -181.598>, <94.2975, -180.721>//circle
				<94.2975, -180.721>, <94.2975, -179.844>, <95.00800000000001, -179.1335>, <95.885, -179.1335>//circle
				<95.885, -67.37349999999999>, <96.762, -67.37349999999999>, <97.47250000000001, -68.084>, <97.47250000000001, -68.961>//circle
				<97.47250000000001, -68.961>, <97.47250000000001, -69.838>, <96.762, -70.5485>, <95.885, -70.5485>//circle
				<95.885, -70.5485>, <95.00800000000001, -70.5485>, <94.2975, -69.838>, <94.2975, -68.961>//circle
				<94.2975, -68.961>, <94.2975, -68.084>, <95.00800000000001, -67.37349999999999>, <95.885, -67.37349999999999>//circle
				<123.317, -179.1335>, <124.19399999999999, -179.1335>, <124.9045, -179.844>, <124.9045, -180.721>//circle
				<124.9045, -180.721>, <124.9045, -181.598>, <124.19399999999999, -182.3085>, <123.317, -182.3085>//circle
				<123.317, -182.3085>, <122.44, -182.3085>, <121.72949999999999, -181.598>, <121.72949999999999, -180.721>//circle
				<121.72949999999999, -180.721>, <121.72949999999999, -179.844>, <122.44, -179.1335>, <123.317, -179.1335>//circle
				<123.317, -67.37349999999999>, <124.19399999999999, -67.37349999999999>, <124.9045, -68.084>, <124.9045, -68.961>//circle
				<124.9045, -68.961>, <124.9045, -69.838>, <124.19399999999999, -70.5485>, <123.317, -70.5485>//circle
				<123.317, -70.5485>, <122.44, -70.5485>, <121.72949999999999, -69.838>, <121.72949999999999, -68.961>//circle
				<121.72949999999999, -68.961>, <121.72949999999999, -68.084>, <122.44, -67.37349999999999>, <123.317, -67.37349999999999>//circle
				<95.885, -174.05349999999999>, <96.762, -174.05349999999999>, <97.47250000000001, -174.76399999999998>, <97.47250000000001, -175.641>//circle
				<97.47250000000001, -175.641>, <97.47250000000001, -176.518>, <96.762, -177.2285>, <95.885, -177.2285>//circle
				<95.885, -177.2285>, <95.00800000000001, -177.2285>, <94.2975, -176.518>, <94.2975, -175.641>//circle
				<94.2975, -175.641>, <94.2975, -174.76399999999998>, <95.00800000000001, -174.05349999999999>, <95.885, -174.05349999999999>//circle
				<95.885, -62.293499999999995>, <96.762, -62.293499999999995>, <97.47250000000001, -63.004>, <97.47250000000001, -63.881>//circle
				<97.47250000000001, -63.881>, <97.47250000000001, -64.758>, <96.762, -65.4685>, <95.885, -65.4685>//circle
				<95.885, -65.4685>, <95.00800000000001, -65.4685>, <94.2975, -64.758>, <94.2975, -63.881>//circle
				<94.2975, -63.881>, <94.2975, -63.004>, <95.00800000000001, -62.293499999999995>, <95.885, -62.293499999999995>//circle
				<123.317, -174.05349999999999>, <124.19399999999999, -174.05349999999999>, <124.9045, -174.76399999999998>, <124.9045, -175.641>//circle
				<124.9045, -175.641>, <124.9045, -176.518>, <124.19399999999999, -177.2285>, <123.317, -177.2285>//circle
				<123.317, -177.2285>, <122.44, -177.2285>, <121.72949999999999, -176.518>, <121.72949999999999, -175.641>//circle
				<121.72949999999999, -175.641>, <121.72949999999999, -174.76399999999998>, <122.44, -174.05349999999999>, <123.317, -174.05349999999999>//circle
				<123.317, -62.293499999999995>, <124.19399999999999, -62.293499999999995>, <124.9045, -63.004>, <124.9045, -63.881>//circle
				<124.9045, -63.881>, <124.9045, -64.758>, <124.19399999999999, -65.4685>, <123.317, -65.4685>//circle
				<123.317, -65.4685>, <122.44, -65.4685>, <121.72949999999999, -64.758>, <121.72949999999999, -63.881>//circle
				<121.72949999999999, -63.881>, <121.72949999999999, -63.004>, <122.44, -62.293499999999995>, <123.317, -62.293499999999995>//circle
				<95.885, -168.9735>, <96.762, -168.9735>, <97.47250000000001, -169.684>, <97.47250000000001, -170.561>//circle
				<97.47250000000001, -170.561>, <97.47250000000001, -171.43800000000002>, <96.762, -172.1485>, <95.885, -172.1485>//circle
				<95.885, -172.1485>, <95.00800000000001, -172.1485>, <94.2975, -171.43800000000002>, <94.2975, -170.561>//circle
				<94.2975, -170.561>, <94.2975, -169.684>, <95.00800000000001, -168.9735>, <95.885, -168.9735>//circle
				<95.885, -57.213499999999996>, <96.762, -57.213499999999996>, <97.47250000000001, -57.924>, <97.47250000000001, -58.801>//circle
				<97.47250000000001, -58.801>, <97.47250000000001, -59.678000000000004>, <96.762, -60.38850000000001>, <95.885, -60.38850000000001>//circle
				<95.885, -60.38850000000001>, <95.00800000000001, -60.38850000000001>, <94.2975, -59.678000000000004>, <94.2975, -58.801>//circle
				<94.2975, -58.801>, <94.2975, -57.924>, <95.00800000000001, -57.213499999999996>, <95.885, -57.213499999999996>//circle
				<123.317, -168.9735>, <124.19399999999999, -168.9735>, <124.9045, -169.684>, <124.9045, -170.561>//circle
				<124.9045, -170.561>, <124.9045, -171.43800000000002>, <124.19399999999999, -172.1485>, <123.317, -172.1485>//circle
				<123.317, -172.1485>, <122.44, -172.1485>, <121.72949999999999, -171.43800000000002>, <121.72949999999999, -170.561>//circle
				<121.72949999999999, -170.561>, <121.72949999999999, -169.684>, <122.44, -168.9735>, <123.317, -168.9735>//circle
				<123.317, -57.213499999999996>, <124.19399999999999, -57.213499999999996>, <124.9045, -57.924>, <124.9045, -58.801>//circle
				<124.9045, -58.801>, <124.9045, -59.678000000000004>, <124.19399999999999, -60.38850000000001>, <123.317, -60.38850000000001>//circle
				<123.317, -60.38850000000001>, <122.44, -60.38850000000001>, <121.72949999999999, -59.678000000000004>, <121.72949999999999, -58.801>//circle
				<121.72949999999999, -58.801>, <121.72949999999999, -57.924>, <122.44, -57.213499999999996>, <123.317, -57.213499999999996>//circle
				<95.885, -163.8935>, <96.762, -163.8935>, <97.47250000000001, -164.60399999999998>, <97.47250000000001, -165.481>//circle
				<97.47250000000001, -165.481>, <97.47250000000001, -166.358>, <96.762, -167.0685>, <95.885, -167.0685>//circle
				<95.885, -167.0685>, <95.00800000000001, -167.0685>, <94.2975, -166.358>, <94.2975, -165.481>//circle
				<94.2975, -165.481>, <94.2975, -164.60399999999998>, <95.00800000000001, -163.8935>, <95.885, -163.8935>//circle
				<95.885, -52.13349999999999>, <96.762, -52.13349999999999>, <97.47250000000001, -52.843999999999994>, <97.47250000000001, -53.721>//circle
				<97.47250000000001, -53.721>, <97.47250000000001, -54.598>, <96.762, -55.3085>, <95.885, -55.3085>//circle
				<95.885, -55.3085>, <95.00800000000001, -55.3085>, <94.2975, -54.598>, <94.2975, -53.721>//circle
				<94.2975, -53.721>, <94.2975, -52.843999999999994>, <95.00800000000001, -52.13349999999999>, <95.885, -52.13349999999999>//circle
				<123.317, -163.8935>, <124.19399999999999, -163.8935>, <124.9045, -164.60399999999998>, <124.9045, -165.481>//circle
				<124.9045, -165.481>, <124.9045, -166.358>, <124.19399999999999, -167.0685>, <123.317, -167.0685>//circle
				<123.317, -167.0685>, <122.44, -167.0685>, <121.72949999999999, -166.358>, <121.72949999999999, -165.481>//circle
				<121.72949999999999, -165.481>, <121.72949999999999, -164.60399999999998>, <122.44, -163.8935>, <123.317, -163.8935>//circle
				<123.317, -52.13349999999999>, <124.19399999999999, -52.13349999999999>, <124.9045, -52.843999999999994>, <124.9045, -53.721>//circle
				<124.9045, -53.721>, <124.9045, -54.598>, <124.19399999999999, -55.3085>, <123.317, -55.3085>//circle
				<123.317, -55.3085>, <122.44, -55.3085>, <121.72949999999999, -54.598>, <121.72949999999999, -53.721>//circle
				<121.72949999999999, -53.721>, <121.72949999999999, -52.843999999999994>, <122.44, -52.13349999999999>, <123.317, -52.13349999999999>//circle
				<95.885, -158.8135>, <96.762, -158.8135>, <97.47250000000001, -159.524>, <97.47250000000001, -160.401>//circle
				<97.47250000000001, -160.401>, <97.47250000000001, -161.27800000000002>, <96.762, -161.98850000000002>, <95.885, -161.98850000000002>//circle
				<95.885, -161.98850000000002>, <95.00800000000001, -161.98850000000002>, <94.2975, -161.27800000000002>, <94.2975, -160.401>//circle
				<94.2975, -160.401>, <94.2975, -159.524>, <95.00800000000001, -158.8135>, <95.885, -158.8135>//circle
				<95.885, -47.05349999999999>, <96.762, -47.05349999999999>, <97.47250000000001, -47.763999999999996>, <97.47250000000001, -48.641>//circle
				<97.47250000000001, -48.641>, <97.47250000000001, -49.518>, <96.762, -50.228500000000004>, <95.885, -50.228500000000004>//circle
				<95.885, -50.228500000000004>, <95.00800000000001, -50.228500000000004>, <94.2975, -49.518>, <94.2975, -48.641>//circle
				<94.2975, -48.641>, <94.2975, -47.763999999999996>, <95.00800000000001, -47.05349999999999>, <95.885, -47.05349999999999>//circle
				<123.317, -158.8135>, <124.19399999999999, -158.8135>, <124.9045, -159.524>, <124.9045, -160.401>//circle
				<124.9045, -160.401>, <124.9045, -161.27800000000002>, <124.19399999999999, -161.98850000000002>, <123.317, -161.98850000000002>//circle
				<123.317, -161.98850000000002>, <122.44, -161.98850000000002>, <121.72949999999999, -161.27800000000002>, <121.72949999999999, -160.401>//circle
				<121.72949999999999, -160.401>, <121.72949999999999, -159.524>, <122.44, -158.8135>, <123.317, -158.8135>//circle
				<123.317, -47.05349999999999>, <124.19399999999999, -47.05349999999999>, <124.9045, -47.763999999999996>, <124.9045, -48.641>//circle
				<124.9045, -48.641>, <124.9045, -49.518>, <124.19399999999999, -50.228500000000004>, <123.317, -50.228500000000004>//circle
				<123.317, -50.228500000000004>, <122.44, -50.228500000000004>, <121.72949999999999, -49.518>, <121.72949999999999, -48.641>//circle
				<121.72949999999999, -48.641>, <121.72949999999999, -47.763999999999996>, <122.44, -47.05349999999999>, <123.317, -47.05349999999999>//circle
				<116.205, -158.8135>, <117.082, -158.8135>, <117.7925, -159.524>, <117.7925, -160.401>//circle
				<117.7925, -160.401>, <117.7925, -161.27800000000002>, <117.082, -161.98850000000002>, <116.205, -161.98850000000002>//circle
				<116.205, -161.98850000000002>, <115.328, -161.98850000000002>, <114.61749999999999, -161.27800000000002>, <114.61749999999999, -160.401>//circle
				<114.61749999999999, -160.401>, <114.61749999999999, -159.524>, <115.328, -158.8135>, <116.205, -158.8135>//circle
				<116.205, -47.05349999999999>, <117.082, -47.05349999999999>, <117.7925, -47.763999999999996>, <117.7925, -48.641>//circle
				<117.7925, -48.641>, <117.7925, -49.518>, <117.082, -50.228500000000004>, <116.205, -50.228500000000004>//circle
				<116.205, -50.228500000000004>, <115.328, -50.228500000000004>, <114.61749999999999, -49.518>, <114.61749999999999, -48.641>//circle
				<114.61749999999999, -48.641>, <114.61749999999999, -47.763999999999996>, <115.328, -47.05349999999999>, <116.205, -47.05349999999999>//circle
				<143.637, -158.8135>, <144.514, -158.8135>, <145.2245, -159.524>, <145.2245, -160.401>//circle
				<145.2245, -160.401>, <145.2245, -161.27800000000002>, <144.514, -161.98850000000002>, <143.637, -161.98850000000002>//circle
				<143.637, -161.98850000000002>, <142.76, -161.98850000000002>, <142.0495, -161.27800000000002>, <142.0495, -160.401>//circle
				<142.0495, -160.401>, <142.0495, -159.524>, <142.76, -158.8135>, <143.637, -158.8135>//circle
				<143.637, -47.05349999999999>, <144.514, -47.05349999999999>, <145.2245, -47.763999999999996>, <145.2245, -48.641>//circle
				<145.2245, -48.641>, <145.2245, -49.518>, <144.514, -50.228500000000004>, <143.637, -50.228500000000004>//circle
				<143.637, -50.228500000000004>, <142.76, -50.228500000000004>, <142.0495, -49.518>, <142.0495, -48.641>//circle
				<142.0495, -48.641>, <142.0495, -47.763999999999996>, <142.76, -47.05349999999999>, <143.637, -47.05349999999999>//circle
				<116.205, -163.8935>, <117.082, -163.8935>, <117.7925, -164.60399999999998>, <117.7925, -165.481>//circle
				<117.7925, -165.481>, <117.7925, -166.358>, <117.082, -167.0685>, <116.205, -167.0685>//circle
				<116.205, -167.0685>, <115.328, -167.0685>, <114.61749999999999, -166.358>, <114.61749999999999, -165.481>//circle
				<114.61749999999999, -165.481>, <114.61749999999999, -164.60399999999998>, <115.328, -163.8935>, <116.205, -163.8935>//circle
				<116.205, -52.13349999999999>, <117.082, -52.13349999999999>, <117.7925, -52.843999999999994>, <117.7925, -53.721>//circle
				<117.7925, -53.721>, <117.7925, -54.598>, <117.082, -55.3085>, <116.205, -55.3085>//circle
				<116.205, -55.3085>, <115.328, -55.3085>, <114.61749999999999, -54.598>, <114.61749999999999, -53.721>//circle
				<114.61749999999999, -53.721>, <114.61749999999999, -52.843999999999994>, <115.328, -52.13349999999999>, <116.205, -52.13349999999999>//circle
				<143.637, -163.8935>, <144.514, -163.8935>, <145.2245, -164.60399999999998>, <145.2245, -165.481>//circle
				<145.2245, -165.481>, <145.2245, -166.358>, <144.514, -167.0685>, <143.637, -167.0685>//circle
				<143.637, -167.0685>, <142.76, -167.0685>, <142.0495, -166.358>, <142.0495, -165.481>//circle
				<142.0495, -165.481>, <142.0495, -164.60399999999998>, <142.76, -163.8935>, <143.637, -163.8935>//circle
				<143.637, -52.13349999999999>, <144.514, -52.13349999999999>, <145.2245, -52.843999999999994>, <145.2245, -53.721>//circle
				<145.2245, -53.721>, <145.2245, -54.598>, <144.514, -55.3085>, <143.637, -55.3085>//circle
				<143.637, -55.3085>, <142.76, -55.3085>, <142.0495, -54.598>, <142.0495, -53.721>//circle
				<142.0495, -53.721>, <142.0495, -52.843999999999994>, <142.76, -52.13349999999999>, <143.637, -52.13349999999999>//circle
				<116.205, -168.9735>, <117.082, -168.9735>, <117.7925, -169.684>, <117.7925, -170.561>//circle
				<117.7925, -170.561>, <117.7925, -171.43800000000002>, <117.082, -172.1485>, <116.205, -172.1485>//circle
				<116.205, -172.1485>, <115.328, -172.1485>, <114.61749999999999, -171.43800000000002>, <114.61749999999999, -170.561>//circle
				<114.61749999999999, -170.561>, <114.61749999999999, -169.684>, <115.328, -168.9735>, <116.205, -168.9735>//circle
				<116.205, -57.213499999999996>, <117.082, -57.213499999999996>, <117.7925, -57.924>, <117.7925, -58.801>//circle
				<117.7925, -58.801>, <117.7925, -59.678000000000004>, <117.082, -60.38850000000001>, <116.205, -60.38850000000001>//circle
				<116.205, -60.38850000000001>, <115.328, -60.38850000000001>, <114.61749999999999, -59.678000000000004>, <114.61749999999999, -58.801>//circle
				<114.61749999999999, -58.801>, <114.61749999999999, -57.924>, <115.328, -57.213499999999996>, <116.205, -57.213499999999996>//circle
				<143.637, -168.9735>, <144.514, -168.9735>, <145.2245, -169.684>, <145.2245, -170.561>//circle
				<145.2245, -170.561>, <145.2245, -171.43800000000002>, <144.514, -172.1485>, <143.637, -172.1485>//circle
				<143.637, -172.1485>, <142.76, -172.1485>, <142.0495, -171.43800000000002>, <142.0495, -170.561>//circle
				<142.0495, -170.561>, <142.0495, -169.684>, <142.76, -168.9735>, <143.637, -168.9735>//circle
				<143.637, -57.213499999999996>, <144.514, -57.213499999999996>, <145.2245, -57.924>, <145.2245, -58.801>//circle
				<145.2245, -58.801>, <145.2245, -59.678000000000004>, <144.514, -60.38850000000001>, <143.637, -60.38850000000001>//circle
				<143.637, -60.38850000000001>, <142.76, -60.38850000000001>, <142.0495, -59.678000000000004>, <142.0495, -58.801>//circle
				<142.0495, -58.801>, <142.0495, -57.924>, <142.76, -57.213499999999996>, <143.637, -57.213499999999996>//circle
				<116.205, -174.05349999999999>, <117.082, -174.05349999999999>, <117.7925, -174.76399999999998>, <117.7925, -175.641>//circle
				<117.7925, -175.641>, <117.7925, -176.518>, <117.082, -177.2285>, <116.205, -177.2285>//circle
				<116.205, -177.2285>, <115.328, -177.2285>, <114.61749999999999, -176.518>, <114.61749999999999, -175.641>//circle
				<114.61749999999999, -175.641>, <114.61749999999999, -174.76399999999998>, <115.328, -174.05349999999999>, <116.205, -174.05349999999999>//circle
				<116.205, -62.293499999999995>, <117.082, -62.293499999999995>, <117.7925, -63.004>, <117.7925, -63.881>//circle
				<117.7925, -63.881>, <117.7925, -64.758>, <117.082, -65.4685>, <116.205, -65.4685>//circle
				<116.205, -65.4685>, <115.328, -65.4685>, <114.61749999999999, -64.758>, <114.61749999999999, -63.881>//circle
				<114.61749999999999, -63.881>, <114.61749999999999, -63.004>, <115.328, -62.293499999999995>, <116.205, -62.293499999999995>//circle
				<143.637, -174.05349999999999>, <144.514, -174.05349999999999>, <145.2245, -174.76399999999998>, <145.2245, -175.641>//circle
				<145.2245, -175.641>, <145.2245, -176.518>, <144.514, -177.2285>, <143.637, -177.2285>//circle
				<143.637, -177.2285>, <142.76, -177.2285>, <142.0495, -176.518>, <142.0495, -175.641>//circle
				<142.0495, -175.641>, <142.0495, -174.76399999999998>, <142.76, -174.05349999999999>, <143.637, -174.05349999999999>//circle
				<143.637, -62.293499999999995>, <144.514, -62.293499999999995>, <145.2245, -63.004>, <145.2245, -63.881>//circle
				<145.2245, -63.881>, <145.2245, -64.758>, <144.514, -65.4685>, <143.637, -65.4685>//circle
				<143.637, -65.4685>, <142.76, -65.4685>, <142.0495, -64.758>, <142.0495, -63.881>//circle
				<142.0495, -63.881>, <142.0495, -63.004>, <142.76, -62.293499999999995>, <143.637, -62.293499999999995>//circle
				<116.205, -179.1335>, <117.082, -179.1335>, <117.7925, -179.844>, <117.7925, -180.721>//circle
				<117.7925, -180.721>, <117.7925, -181.598>, <117.082, -182.3085>, <116.205, -182.3085>//circle
				<116.205, -182.3085>, <115.328, -182.3085>, <114.61749999999999, -181.598>, <114.61749999999999, -180.721>//circle
				<114.61749999999999, -180.721>, <114.61749999999999, -179.844>, <115.328, -179.1335>, <116.205, -179.1335>//circle
				<116.205, -67.37349999999999>, <117.082, -67.37349999999999>, <117.7925, -68.084>, <117.7925, -68.961>//circle
				<117.7925, -68.961>, <117.7925, -69.838>, <117.082, -70.5485>, <116.205, -70.5485>//circle
				<116.205, -70.5485>, <115.328, -70.5485>, <114.61749999999999, -69.838>, <114.61749999999999, -68.961>//circle
				<114.61749999999999, -68.961>, <114.61749999999999, -68.084>, <115.328, -67.37349999999999>, <116.205, -67.37349999999999>//circle
				<143.637, -179.1335>, <144.514, -179.1335>, <145.2245, -179.844>, <145.2245, -180.721>//circle
				<145.2245, -180.721>, <145.2245, -181.598>, <144.514, -182.3085>, <143.637, -182.3085>//circle
				<143.637, -182.3085>, <142.76, -182.3085>, <142.0495, -181.598>, <142.0495, -180.721>//circle
				<142.0495, -180.721>, <142.0495, -179.844>, <142.76, -179.1335>, <143.637, -179.1335>//circle
				<143.637, -67.37349999999999>, <144.514, -67.37349999999999>, <145.2245, -68.084>, <145.2245, -68.961>//circle
				<145.2245, -68.961>, <145.2245, -69.838>, <144.514, -70.5485>, <143.637, -70.5485>//circle
				<143.637, -70.5485>, <142.76, -70.5485>, <142.0495, -69.838>, <142.0495, -68.961>//circle
				<142.0495, -68.961>, <142.0495, -68.084>, <142.76, -67.37349999999999>, <143.637, -67.37349999999999>//circle
				<116.205, -184.21349999999998>, <117.082, -184.21349999999998>, <117.7925, -184.92399999999998>, <117.7925, -185.801>//circle
				<117.7925, -185.801>, <117.7925, -186.678>, <117.082, -187.3885>, <116.205, -187.3885>//circle
				<116.205, -187.3885>, <115.328, -187.3885>, <114.61749999999999, -186.678>, <114.61749999999999, -185.801>//circle
				<114.61749999999999, -185.801>, <114.61749999999999, -184.92399999999998>, <115.328, -184.21349999999998>, <116.205, -184.21349999999998>//circle
				<116.205, -72.45349999999999>, <117.082, -72.45349999999999>, <117.7925, -73.164>, <117.7925, -74.041>//circle
				<117.7925, -74.041>, <117.7925, -74.91799999999999>, <117.082, -75.6285>, <116.205, -75.6285>//circle
				<116.205, -75.6285>, <115.328, -75.6285>, <114.61749999999999, -74.91799999999999>, <114.61749999999999, -74.041>//circle
				<114.61749999999999, -74.041>, <114.61749999999999, -73.164>, <115.328, -72.45349999999999>, <116.205, -72.45349999999999>//circle
				<143.637, -184.21349999999998>, <144.514, -184.21349999999998>, <145.2245, -184.92399999999998>, <145.2245, -185.801>//circle
				<145.2245, -185.801>, <145.2245, -186.678>, <144.514, -187.3885>, <143.637, -187.3885>//circle
				<143.637, -187.3885>, <142.76, -187.3885>, <142.0495, -186.678>, <142.0495, -185.801>//circle
				<142.0495, -185.801>, <142.0495, -184.92399999999998>, <142.76, -184.21349999999998>, <143.637, -184.21349999999998>//circle
				<143.637, -72.45349999999999>, <144.514, -72.45349999999999>, <145.2245, -73.164>, <145.2245, -74.041>//circle
				<145.2245, -74.041>, <145.2245, -74.91799999999999>, <144.514, -75.6285>, <143.637, -75.6285>//circle
				<143.637, -75.6285>, <142.76, -75.6285>, <142.0495, -74.91799999999999>, <142.0495, -74.041>//circle
				<142.0495, -74.041>, <142.0495, -73.164>, <142.76, -72.45349999999999>, <143.637, -72.45349999999999>//circle
				<111.125, -184.21349999999998>, <112.002, -184.21349999999998>, <112.7125, -184.92399999999998>, <112.7125, -185.801>//circle
				<112.7125, -185.801>, <112.7125, -186.678>, <112.002, -187.3885>, <111.125, -187.3885>//circle
				<111.125, -187.3885>, <110.248, -187.3885>, <109.5375, -186.678>, <109.5375, -185.801>//circle
				<109.5375, -185.801>, <109.5375, -184.92399999999998>, <110.248, -184.21349999999998>, <111.125, -184.21349999999998>//circle
				<111.125, -72.45349999999999>, <112.002, -72.45349999999999>, <112.7125, -73.164>, <112.7125, -74.041>//circle
				<112.7125, -74.041>, <112.7125, -74.91799999999999>, <112.002, -75.6285>, <111.125, -75.6285>//circle
				<111.125, -75.6285>, <110.248, -75.6285>, <109.5375, -74.91799999999999>, <109.5375, -74.041>//circle
				<109.5375, -74.041>, <109.5375, -73.164>, <110.248, -72.45349999999999>, <111.125, -72.45349999999999>//circle
				<138.557, -184.21349999999998>, <139.434, -184.21349999999998>, <140.1445, -184.92399999999998>, <140.1445, -185.801>//circle
				<140.1445, -185.801>, <140.1445, -186.678>, <139.434, -187.3885>, <138.557, -187.3885>//circle
				<138.557, -187.3885>, <137.67999999999998, -187.3885>, <136.96949999999998, -186.678>, <136.96949999999998, -185.801>//circle
				<136.96949999999998, -185.801>, <136.96949999999998, -184.92399999999998>, <137.67999999999998, -184.21349999999998>, <138.557, -184.21349999999998>//circle
				<138.557, -72.45349999999999>, <139.434, -72.45349999999999>, <140.1445, -73.164>, <140.1445, -74.041>//circle
				<140.1445, -74.041>, <140.1445, -74.91799999999999>, <139.434, -75.6285>, <138.557, -75.6285>//circle
				<138.557, -75.6285>, <137.67999999999998, -75.6285>, <136.96949999999998, -74.91799999999999>, <136.96949999999998, -74.041>//circle
				<136.96949999999998, -74.041>, <136.96949999999998, -73.164>, <137.67999999999998, -72.45349999999999>, <138.557, -72.45349999999999>//circle
				<106.045, -184.21349999999998>, <106.922, -184.21349999999998>, <107.63250000000001, -184.92399999999998>, <107.63250000000001, -185.801>//circle
				<107.63250000000001, -185.801>, <107.63250000000001, -186.678>, <106.922, -187.3885>, <106.045, -187.3885>//circle
				<106.045, -187.3885>, <105.168, -187.3885>, <104.4575, -186.678>, <104.4575, -185.801>//circle
				<104.4575, -185.801>, <104.4575, -184.92399999999998>, <105.168, -184.21349999999998>, <106.045, -184.21349999999998>//circle
				<106.045, -72.45349999999999>, <106.922, -72.45349999999999>, <107.63250000000001, -73.164>, <107.63250000000001, -74.041>//circle
				<107.63250000000001, -74.041>, <107.63250000000001, -74.91799999999999>, <106.922, -75.6285>, <106.045, -75.6285>//circle
				<106.045, -75.6285>, <105.168, -75.6285>, <104.4575, -74.91799999999999>, <104.4575, -74.041>//circle
				<104.4575, -74.041>, <104.4575, -73.164>, <105.168, -72.45349999999999>, <106.045, -72.45349999999999>//circle
				<133.477, -184.21349999999998>, <134.354, -184.21349999999998>, <135.0645, -184.92399999999998>, <135.0645, -185.801>//circle
				<135.0645, -185.801>, <135.0645, -186.678>, <134.354, -187.3885>, <133.477, -187.3885>//circle
				<133.477, -187.3885>, <132.6, -187.3885>, <131.8895, -186.678>, <131.8895, -185.801>//circle
				<131.8895, -185.801>, <131.8895, -184.92399999999998>, <132.6, -184.21349999999998>, <133.477, -184.21349999999998>//circle
				<133.477, -72.45349999999999>, <134.354, -72.45349999999999>, <135.0645, -73.164>, <135.0645, -74.041>//circle
				<135.0645, -74.041>, <135.0645, -74.91799999999999>, <134.354, -75.6285>, <133.477, -75.6285>//circle
				<133.477, -75.6285>, <132.6, -75.6285>, <131.8895, -74.91799999999999>, <131.8895, -74.041>//circle
				<131.8895, -74.041>, <131.8895, -73.164>, <132.6, -72.45349999999999>, <133.477, -72.45349999999999>//circle
				<100.965, -184.21349999999998>, <101.842, -184.21349999999998>, <102.55250000000001, -184.92399999999998>, <102.55250000000001, -185.801>//circle
				<102.55250000000001, -185.801>, <102.55250000000001, -186.678>, <101.842, -187.3885>, <100.965, -187.3885>//circle
				<100.965, -187.3885>, <100.08800000000001, -187.3885>, <99.3775, -186.678>, <99.3775, -185.801>//circle
				<99.3775, -185.801>, <99.3775, -184.92399999999998>, <100.08800000000001, -184.21349999999998>, <100.965, -184.21349999999998>//circle
				<100.965, -72.45349999999999>, <101.842, -72.45349999999999>, <102.55250000000001, -73.164>, <102.55250000000001, -74.041>//circle
				<102.55250000000001, -74.041>, <102.55250000000001, -74.91799999999999>, <101.842, -75.6285>, <100.965, -75.6285>//circle
				<100.965, -75.6285>, <100.08800000000001, -75.6285>, <99.3775, -74.91799999999999>, <99.3775, -74.041>//circle
				<99.3775, -74.041>, <99.3775, -73.164>, <100.08800000000001, -72.45349999999999>, <100.965, -72.45349999999999>//circle
				<128.397, -184.21349999999998>, <129.274, -184.21349999999998>, <129.9845, -184.92399999999998>, <129.9845, -185.801>//circle
				<129.9845, -185.801>, <129.9845, -186.678>, <129.274, -187.3885>, <128.397, -187.3885>//circle
				<128.397, -187.3885>, <127.52, -187.3885>, <126.80949999999999, -186.678>, <126.80949999999999, -185.801>//circle
				<126.80949999999999, -185.801>, <126.80949999999999, -184.92399999999998>, <127.52, -184.21349999999998>, <128.397, -184.21349999999998>//circle
				<128.397, -72.45349999999999>, <129.274, -72.45349999999999>, <129.9845, -73.164>, <129.9845, -74.041>//circle
				<129.9845, -74.041>, <129.9845, -74.91799999999999>, <129.274, -75.6285>, <128.397, -75.6285>//circle
				<128.397, -75.6285>, <127.52, -75.6285>, <126.80949999999999, -74.91799999999999>, <126.80949999999999, -74.041>//circle
				<126.80949999999999, -74.041>, <126.80949999999999, -73.164>, <127.52, -72.45349999999999>, <128.397, -72.45349999999999>//circle
				<100.965, -179.1335>, <101.842, -179.1335>, <102.55250000000001, -179.844>, <102.55250000000001, -180.721>//circle
				<102.55250000000001, -180.721>, <102.55250000000001, -181.598>, <101.842, -182.3085>, <100.965, -182.3085>//circle
				<100.965, -182.3085>, <100.08800000000001, -182.3085>, <99.3775, -181.598>, <99.3775, -180.721>//circle
				<99.3775, -180.721>, <99.3775, -179.844>, <100.08800000000001, -179.1335>, <100.965, -179.1335>//circle
				<100.965, -67.37349999999999>, <101.842, -67.37349999999999>, <102.55250000000001, -68.084>, <102.55250000000001, -68.961>//circle
				<102.55250000000001, -68.961>, <102.55250000000001, -69.838>, <101.842, -70.5485>, <100.965, -70.5485>//circle
				<100.965, -70.5485>, <100.08800000000001, -70.5485>, <99.3775, -69.838>, <99.3775, -68.961>//circle
				<99.3775, -68.961>, <99.3775, -68.084>, <100.08800000000001, -67.37349999999999>, <100.965, -67.37349999999999>//circle
				<128.397, -179.1335>, <129.274, -179.1335>, <129.9845, -179.844>, <129.9845, -180.721>//circle
				<129.9845, -180.721>, <129.9845, -181.598>, <129.274, -182.3085>, <128.397, -182.3085>//circle
				<128.397, -182.3085>, <127.52, -182.3085>, <126.80949999999999, -181.598>, <126.80949999999999, -180.721>//circle
				<126.80949999999999, -180.721>, <126.80949999999999, -179.844>, <127.52, -179.1335>, <128.397, -179.1335>//circle
				<128.397, -67.37349999999999>, <129.274, -67.37349999999999>, <129.9845, -68.084>, <129.9845, -68.961>//circle
				<129.9845, -68.961>, <129.9845, -69.838>, <129.274, -70.5485>, <128.397, -70.5485>//circle
				<128.397, -70.5485>, <127.52, -70.5485>, <126.80949999999999, -69.838>, <126.80949999999999, -68.961>//circle
				<126.80949999999999, -68.961>, <126.80949999999999, -68.084>, <127.52, -67.37349999999999>, <128.397, -67.37349999999999>//circle
				<106.045, -179.1335>, <106.922, -179.1335>, <107.63250000000001, -179.844>, <107.63250000000001, -180.721>//circle
				<107.63250000000001, -180.721>, <107.63250000000001, -181.598>, <106.922, -182.3085>, <106.045, -182.3085>//circle
				<106.045, -182.3085>, <105.168, -182.3085>, <104.4575, -181.598>, <104.4575, -180.721>//circle
				<104.4575, -180.721>, <104.4575, -179.844>, <105.168, -179.1335>, <106.045, -179.1335>//circle
				<106.045, -67.37349999999999>, <106.922, -67.37349999999999>, <107.63250000000001, -68.084>, <107.63250000000001, -68.961>//circle
				<107.63250000000001, -68.961>, <107.63250000000001, -69.838>, <106.922, -70.5485>, <106.045, -70.5485>//circle
				<106.045, -70.5485>, <105.168, -70.5485>, <104.4575, -69.838>, <104.4575, -68.961>//circle
				<104.4575, -68.961>, <104.4575, -68.084>, <105.168, -67.37349999999999>, <106.045, -67.37349999999999>//circle
				<133.477, -179.1335>, <134.354, -179.1335>, <135.0645, -179.844>, <135.0645, -180.721>//circle
				<135.0645, -180.721>, <135.0645, -181.598>, <134.354, -182.3085>, <133.477, -182.3085>//circle
				<133.477, -182.3085>, <132.6, -182.3085>, <131.8895, -181.598>, <131.8895, -180.721>//circle
				<131.8895, -180.721>, <131.8895, -179.844>, <132.6, -179.1335>, <133.477, -179.1335>//circle
				<133.477, -67.37349999999999>, <134.354, -67.37349999999999>, <135.0645, -68.084>, <135.0645, -68.961>//circle
				<135.0645, -68.961>, <135.0645, -69.838>, <134.354, -70.5485>, <133.477, -70.5485>//circle
				<133.477, -70.5485>, <132.6, -70.5485>, <131.8895, -69.838>, <131.8895, -68.961>//circle
				<131.8895, -68.961>, <131.8895, -68.084>, <132.6, -67.37349999999999>, <133.477, -67.37349999999999>//circle
				<111.125, -179.1335>, <112.002, -179.1335>, <112.7125, -179.844>, <112.7125, -180.721>//circle
				<112.7125, -180.721>, <112.7125, -181.598>, <112.002, -182.3085>, <111.125, -182.3085>//circle
				<111.125, -182.3085>, <110.248, -182.3085>, <109.5375, -181.598>, <109.5375, -180.721>//circle
				<109.5375, -180.721>, <109.5375, -179.844>, <110.248, -179.1335>, <111.125, -179.1335>//circle
				<111.125, -67.37349999999999>, <112.002, -67.37349999999999>, <112.7125, -68.084>, <112.7125, -68.961>//circle
				<112.7125, -68.961>, <112.7125, -69.838>, <112.002, -70.5485>, <111.125, -70.5485>//circle
				<111.125, -70.5485>, <110.248, -70.5485>, <109.5375, -69.838>, <109.5375, -68.961>//circle
				<109.5375, -68.961>, <109.5375, -68.084>, <110.248, -67.37349999999999>, <111.125, -67.37349999999999>//circle
				<138.557, -179.1335>, <139.434, -179.1335>, <140.1445, -179.844>, <140.1445, -180.721>//circle
				<140.1445, -180.721>, <140.1445, -181.598>, <139.434, -182.3085>, <138.557, -182.3085>//circle
				<138.557, -182.3085>, <137.67999999999998, -182.3085>, <136.96949999999998, -181.598>, <136.96949999999998, -180.721>//circle
				<136.96949999999998, -180.721>, <136.96949999999998, -179.844>, <137.67999999999998, -179.1335>, <138.557, -179.1335>//circle
				<138.557, -67.37349999999999>, <139.434, -67.37349999999999>, <140.1445, -68.084>, <140.1445, -68.961>//circle
				<140.1445, -68.961>, <140.1445, -69.838>, <139.434, -70.5485>, <138.557, -70.5485>//circle
				<138.557, -70.5485>, <137.67999999999998, -70.5485>, <136.96949999999998, -69.838>, <136.96949999999998, -68.961>//circle
				<136.96949999999998, -68.961>, <136.96949999999998, -68.084>, <137.67999999999998, -67.37349999999999>, <138.557, -67.37349999999999>//circle
				<111.125, -174.05349999999999>, <112.002, -174.05349999999999>, <112.7125, -174.76399999999998>, <112.7125, -175.641>//circle
				<112.7125, -175.641>, <112.7125, -176.518>, <112.002, -177.2285>, <111.125, -177.2285>//circle
				<111.125, -177.2285>, <110.248, -177.2285>, <109.5375, -176.518>, <109.5375, -175.641>//circle
				<109.5375, -175.641>, <109.5375, -174.76399999999998>, <110.248, -174.05349999999999>, <111.125, -174.05349999999999>//circle
				<111.125, -62.293499999999995>, <112.002, -62.293499999999995>, <112.7125, -63.004>, <112.7125, -63.881>//circle
				<112.7125, -63.881>, <112.7125, -64.758>, <112.002, -65.4685>, <111.125, -65.4685>//circle
				<111.125, -65.4685>, <110.248, -65.4685>, <109.5375, -64.758>, <109.5375, -63.881>//circle
				<109.5375, -63.881>, <109.5375, -63.004>, <110.248, -62.293499999999995>, <111.125, -62.293499999999995>//circle
				<138.557, -174.05349999999999>, <139.434, -174.05349999999999>, <140.1445, -174.76399999999998>, <140.1445, -175.641>//circle
				<140.1445, -175.641>, <140.1445, -176.518>, <139.434, -177.2285>, <138.557, -177.2285>//circle
				<138.557, -177.2285>, <137.67999999999998, -177.2285>, <136.96949999999998, -176.518>, <136.96949999999998, -175.641>//circle
				<136.96949999999998, -175.641>, <136.96949999999998, -174.76399999999998>, <137.67999999999998, -174.05349999999999>, <138.557, -174.05349999999999>//circle
				<138.557, -62.293499999999995>, <139.434, -62.293499999999995>, <140.1445, -63.004>, <140.1445, -63.881>//circle
				<140.1445, -63.881>, <140.1445, -64.758>, <139.434, -65.4685>, <138.557, -65.4685>//circle
				<138.557, -65.4685>, <137.67999999999998, -65.4685>, <136.96949999999998, -64.758>, <136.96949999999998, -63.881>//circle
				<136.96949999999998, -63.881>, <136.96949999999998, -63.004>, <137.67999999999998, -62.293499999999995>, <138.557, -62.293499999999995>//circle
				<106.045, -174.05349999999999>, <106.922, -174.05349999999999>, <107.63250000000001, -174.76399999999998>, <107.63250000000001, -175.641>//circle
				<107.63250000000001, -175.641>, <107.63250000000001, -176.518>, <106.922, -177.2285>, <106.045, -177.2285>//circle
				<106.045, -177.2285>, <105.168, -177.2285>, <104.4575, -176.518>, <104.4575, -175.641>//circle
				<104.4575, -175.641>, <104.4575, -174.76399999999998>, <105.168, -174.05349999999999>, <106.045, -174.05349999999999>//circle
				<106.045, -62.293499999999995>, <106.922, -62.293499999999995>, <107.63250000000001, -63.004>, <107.63250000000001, -63.881>//circle
				<107.63250000000001, -63.881>, <107.63250000000001, -64.758>, <106.922, -65.4685>, <106.045, -65.4685>//circle
				<106.045, -65.4685>, <105.168, -65.4685>, <104.4575, -64.758>, <104.4575, -63.881>//circle
				<104.4575, -63.881>, <104.4575, -63.004>, <105.168, -62.293499999999995>, <106.045, -62.293499999999995>//circle
				<133.477, -174.05349999999999>, <134.354, -174.05349999999999>, <135.0645, -174.76399999999998>, <135.0645, -175.641>//circle
				<135.0645, -175.641>, <135.0645, -176.518>, <134.354, -177.2285>, <133.477, -177.2285>//circle
				<133.477, -177.2285>, <132.6, -177.2285>, <131.8895, -176.518>, <131.8895, -175.641>//circle
				<131.8895, -175.641>, <131.8895, -174.76399999999998>, <132.6, -174.05349999999999>, <133.477, -174.05349999999999>//circle
				<133.477, -62.293499999999995>, <134.354, -62.293499999999995>, <135.0645, -63.004>, <135.0645, -63.881>//circle
				<135.0645, -63.881>, <135.0645, -64.758>, <134.354, -65.4685>, <133.477, -65.4685>//circle
				<133.477, -65.4685>, <132.6, -65.4685>, <131.8895, -64.758>, <131.8895, -63.881>//circle
				<131.8895, -63.881>, <131.8895, -63.004>, <132.6, -62.293499999999995>, <133.477, -62.293499999999995>//circle
				<100.965, -174.05349999999999>, <101.842, -174.05349999999999>, <102.55250000000001, -174.76399999999998>, <102.55250000000001, -175.641>//circle
				<102.55250000000001, -175.641>, <102.55250000000001, -176.518>, <101.842, -177.2285>, <100.965, -177.2285>//circle
				<100.965, -177.2285>, <100.08800000000001, -177.2285>, <99.3775, -176.518>, <99.3775, -175.641>//circle
				<99.3775, -175.641>, <99.3775, -174.76399999999998>, <100.08800000000001, -174.05349999999999>, <100.965, -174.05349999999999>//circle
				<100.965, -62.293499999999995>, <101.842, -62.293499999999995>, <102.55250000000001, -63.004>, <102.55250000000001, -63.881>//circle
				<102.55250000000001, -63.881>, <102.55250000000001, -64.758>, <101.842, -65.4685>, <100.965, -65.4685>//circle
				<100.965, -65.4685>, <100.08800000000001, -65.4685>, <99.3775, -64.758>, <99.3775, -63.881>//circle
				<99.3775, -63.881>, <99.3775, -63.004>, <100.08800000000001, -62.293499999999995>, <100.965, -62.293499999999995>//circle
				<128.397, -174.05349999999999>, <129.274, -174.05349999999999>, <129.9845, -174.76399999999998>, <129.9845, -175.641>//circle
				<129.9845, -175.641>, <129.9845, -176.518>, <129.274, -177.2285>, <128.397, -177.2285>//circle
				<128.397, -177.2285>, <127.52, -177.2285>, <126.80949999999999, -176.518>, <126.80949999999999, -175.641>//circle
				<126.80949999999999, -175.641>, <126.80949999999999, -174.76399999999998>, <127.52, -174.05349999999999>, <128.397, -174.05349999999999>//circle
				<128.397, -62.293499999999995>, <129.274, -62.293499999999995>, <129.9845, -63.004>, <129.9845, -63.881>//circle
				<129.9845, -63.881>, <129.9845, -64.758>, <129.274, -65.4685>, <128.397, -65.4685>//circle
				<128.397, -65.4685>, <127.52, -65.4685>, <126.80949999999999, -64.758>, <126.80949999999999, -63.881>//circle
				<126.80949999999999, -63.881>, <126.80949999999999, -63.004>, <127.52, -62.293499999999995>, <128.397, -62.293499999999995>//circle
				<100.965, -168.9735>, <101.842, -168.9735>, <102.55250000000001, -169.684>, <102.55250000000001, -170.561>//circle
				<102.55250000000001, -170.561>, <102.55250000000001, -171.43800000000002>, <101.842, -172.1485>, <100.965, -172.1485>//circle
				<100.965, -172.1485>, <100.08800000000001, -172.1485>, <99.3775, -171.43800000000002>, <99.3775, -170.561>//circle
				<99.3775, -170.561>, <99.3775, -169.684>, <100.08800000000001, -168.9735>, <100.965, -168.9735>//circle
				<100.965, -57.213499999999996>, <101.842, -57.213499999999996>, <102.55250000000001, -57.924>, <102.55250000000001, -58.801>//circle
				<102.55250000000001, -58.801>, <102.55250000000001, -59.678000000000004>, <101.842, -60.38850000000001>, <100.965, -60.38850000000001>//circle
				<100.965, -60.38850000000001>, <100.08800000000001, -60.38850000000001>, <99.3775, -59.678000000000004>, <99.3775, -58.801>//circle
				<99.3775, -58.801>, <99.3775, -57.924>, <100.08800000000001, -57.213499999999996>, <100.965, -57.213499999999996>//circle
				<128.397, -168.9735>, <129.274, -168.9735>, <129.9845, -169.684>, <129.9845, -170.561>//circle
				<129.9845, -170.561>, <129.9845, -171.43800000000002>, <129.274, -172.1485>, <128.397, -172.1485>//circle
				<128.397, -172.1485>, <127.52, -172.1485>, <126.80949999999999, -171.43800000000002>, <126.80949999999999, -170.561>//circle
				<126.80949999999999, -170.561>, <126.80949999999999, -169.684>, <127.52, -168.9735>, <128.397, -168.9735>//circle
				<128.397, -57.213499999999996>, <129.274, -57.213499999999996>, <129.9845, -57.924>, <129.9845, -58.801>//circle
				<129.9845, -58.801>, <129.9845, -59.678000000000004>, <129.274, -60.38850000000001>, <128.397, -60.38850000000001>//circle
				<128.397, -60.38850000000001>, <127.52, -60.38850000000001>, <126.80949999999999, -59.678000000000004>, <126.80949999999999, -58.801>//circle
				<126.80949999999999, -58.801>, <126.80949999999999, -57.924>, <127.52, -57.213499999999996>, <128.397, -57.213499999999996>//circle
				<106.045, -168.9735>, <106.922, -168.9735>, <107.63250000000001, -169.684>, <107.63250000000001, -170.561>//circle
				<107.63250000000001, -170.561>, <107.63250000000001, -171.43800000000002>, <106.922, -172.1485>, <106.045, -172.1485>//circle
				<106.045, -172.1485>, <105.168, -172.1485>, <104.4575, -171.43800000000002>, <104.4575, -170.561>//circle
				<104.4575, -170.561>, <104.4575, -169.684>, <105.168, -168.9735>, <106.045, -168.9735>//circle
				<106.045, -57.213499999999996>, <106.922, -57.213499999999996>, <107.63250000000001, -57.924>, <107.63250000000001, -58.801>//circle
				<107.63250000000001, -58.801>, <107.63250000000001, -59.678000000000004>, <106.922, -60.38850000000001>, <106.045, -60.38850000000001>//circle
				<106.045, -60.38850000000001>, <105.168, -60.38850000000001>, <104.4575, -59.678000000000004>, <104.4575, -58.801>//circle
				<104.4575, -58.801>, <104.4575, -57.924>, <105.168, -57.213499999999996>, <106.045, -57.213499999999996>//circle
				<133.477, -168.9735>, <134.354, -168.9735>, <135.0645, -169.684>, <135.0645, -170.561>//circle
				<135.0645, -170.561>, <135.0645, -171.43800000000002>, <134.354, -172.1485>, <133.477, -172.1485>//circle
				<133.477, -172.1485>, <132.6, -172.1485>, <131.8895, -171.43800000000002>, <131.8895, -170.561>//circle
				<131.8895, -170.561>, <131.8895, -169.684>, <132.6, -168.9735>, <133.477, -168.9735>//circle
				<133.477, -57.213499999999996>, <134.354, -57.213499999999996>, <135.0645, -57.924>, <135.0645, -58.801>//circle
				<135.0645, -58.801>, <135.0645, -59.678000000000004>, <134.354, -60.38850000000001>, <133.477, -60.38850000000001>//circle
				<133.477, -60.38850000000001>, <132.6, -60.38850000000001>, <131.8895, -59.678000000000004>, <131.8895, -58.801>//circle
				<131.8895, -58.801>, <131.8895, -57.924>, <132.6, -57.213499999999996>, <133.477, -57.213499999999996>//circle
				<111.125, -168.9735>, <112.002, -168.9735>, <112.7125, -169.684>, <112.7125, -170.561>//circle
				<112.7125, -170.561>, <112.7125, -171.43800000000002>, <112.002, -172.1485>, <111.125, -172.1485>//circle
				<111.125, -172.1485>, <110.248, -172.1485>, <109.5375, -171.43800000000002>, <109.5375, -170.561>//circle
				<109.5375, -170.561>, <109.5375, -169.684>, <110.248, -168.9735>, <111.125, -168.9735>//circle
				<111.125, -57.213499999999996>, <112.002, -57.213499999999996>, <112.7125, -57.924>, <112.7125, -58.801>//circle
				<112.7125, -58.801>, <112.7125, -59.678000000000004>, <112.002, -60.38850000000001>, <111.125, -60.38850000000001>//circle
				<111.125, -60.38850000000001>, <110.248, -60.38850000000001>, <109.5375, -59.678000000000004>, <109.5375, -58.801>//circle
				<109.5375, -58.801>, <109.5375, -57.924>, <110.248, -57.213499999999996>, <111.125, -57.213499999999996>//circle
				<138.557, -168.9735>, <139.434, -168.9735>, <140.1445, -169.684>, <140.1445, -170.561>//circle
				<140.1445, -170.561>, <140.1445, -171.43800000000002>, <139.434, -172.1485>, <138.557, -172.1485>//circle
				<138.557, -172.1485>, <137.67999999999998, -172.1485>, <136.96949999999998, -171.43800000000002>, <136.96949999999998, -170.561>//circle
				<136.96949999999998, -170.561>, <136.96949999999998, -169.684>, <137.67999999999998, -168.9735>, <138.557, -168.9735>//circle
				<138.557, -57.213499999999996>, <139.434, -57.213499999999996>, <140.1445, -57.924>, <140.1445, -58.801>//circle
				<140.1445, -58.801>, <140.1445, -59.678000000000004>, <139.434, -60.38850000000001>, <138.557, -60.38850000000001>//circle
				<138.557, -60.38850000000001>, <137.67999999999998, -60.38850000000001>, <136.96949999999998, -59.678000000000004>, <136.96949999999998, -58.801>//circle
				<136.96949999999998, -58.801>, <136.96949999999998, -57.924>, <137.67999999999998, -57.213499999999996>, <138.557, -57.213499999999996>//circle
				<111.125, -163.8935>, <112.002, -163.8935>, <112.7125, -164.60399999999998>, <112.7125, -165.481>//circle
				<112.7125, -165.481>, <112.7125, -166.358>, <112.002, -167.0685>, <111.125, -167.0685>//circle
				<111.125, -167.0685>, <110.248, -167.0685>, <109.5375, -166.358>, <109.5375, -165.481>//circle
				<109.5375, -165.481>, <109.5375, -164.60399999999998>, <110.248, -163.8935>, <111.125, -163.8935>//circle
				<111.125, -52.13349999999999>, <112.002, -52.13349999999999>, <112.7125, -52.843999999999994>, <112.7125, -53.721>//circle
				<112.7125, -53.721>, <112.7125, -54.598>, <112.002, -55.3085>, <111.125, -55.3085>//circle
				<111.125, -55.3085>, <110.248, -55.3085>, <109.5375, -54.598>, <109.5375, -53.721>//circle
				<109.5375, -53.721>, <109.5375, -52.843999999999994>, <110.248, -52.13349999999999>, <111.125, -52.13349999999999>//circle
				<138.557, -163.8935>, <139.434, -163.8935>, <140.1445, -164.60399999999998>, <140.1445, -165.481>//circle
				<140.1445, -165.481>, <140.1445, -166.358>, <139.434, -167.0685>, <138.557, -167.0685>//circle
				<138.557, -167.0685>, <137.67999999999998, -167.0685>, <136.96949999999998, -166.358>, <136.96949999999998, -165.481>//circle
				<136.96949999999998, -165.481>, <136.96949999999998, -164.60399999999998>, <137.67999999999998, -163.8935>, <138.557, -163.8935>//circle
				<138.557, -52.13349999999999>, <139.434, -52.13349999999999>, <140.1445, -52.843999999999994>, <140.1445, -53.721>//circle
				<140.1445, -53.721>, <140.1445, -54.598>, <139.434, -55.3085>, <138.557, -55.3085>//circle
				<138.557, -55.3085>, <137.67999999999998, -55.3085>, <136.96949999999998, -54.598>, <136.96949999999998, -53.721>//circle
				<136.96949999999998, -53.721>, <136.96949999999998, -52.843999999999994>, <137.67999999999998, -52.13349999999999>, <138.557, -52.13349999999999>//circle
				<106.045, -163.8935>, <106.922, -163.8935>, <107.63250000000001, -164.60399999999998>, <107.63250000000001, -165.481>//circle
				<107.63250000000001, -165.481>, <107.63250000000001, -166.358>, <106.922, -167.0685>, <106.045, -167.0685>//circle
				<106.045, -167.0685>, <105.168, -167.0685>, <104.4575, -166.358>, <104.4575, -165.481>//circle
				<104.4575, -165.481>, <104.4575, -164.60399999999998>, <105.168, -163.8935>, <106.045, -163.8935>//circle
				<106.045, -52.13349999999999>, <106.922, -52.13349999999999>, <107.63250000000001, -52.843999999999994>, <107.63250000000001, -53.721>//circle
				<107.63250000000001, -53.721>, <107.63250000000001, -54.598>, <106.922, -55.3085>, <106.045, -55.3085>//circle
				<106.045, -55.3085>, <105.168, -55.3085>, <104.4575, -54.598>, <104.4575, -53.721>//circle
				<104.4575, -53.721>, <104.4575, -52.843999999999994>, <105.168, -52.13349999999999>, <106.045, -52.13349999999999>//circle
				<133.477, -163.8935>, <134.354, -163.8935>, <135.0645, -164.60399999999998>, <135.0645, -165.481>//circle
				<135.0645, -165.481>, <135.0645, -166.358>, <134.354, -167.0685>, <133.477, -167.0685>//circle
				<133.477, -167.0685>, <132.6, -167.0685>, <131.8895, -166.358>, <131.8895, -165.481>//circle
				<131.8895, -165.481>, <131.8895, -164.60399999999998>, <132.6, -163.8935>, <133.477, -163.8935>//circle
				<133.477, -52.13349999999999>, <134.354, -52.13349999999999>, <135.0645, -52.843999999999994>, <135.0645, -53.721>//circle
				<135.0645, -53.721>, <135.0645, -54.598>, <134.354, -55.3085>, <133.477, -55.3085>//circle
				<133.477, -55.3085>, <132.6, -55.3085>, <131.8895, -54.598>, <131.8895, -53.721>//circle
				<131.8895, -53.721>, <131.8895, -52.843999999999994>, <132.6, -52.13349999999999>, <133.477, -52.13349999999999>//circle
				<100.965, -163.8935>, <101.842, -163.8935>, <102.55250000000001, -164.60399999999998>, <102.55250000000001, -165.481>//circle
				<102.55250000000001, -165.481>, <102.55250000000001, -166.358>, <101.842, -167.0685>, <100.965, -167.0685>//circle
				<100.965, -167.0685>, <100.08800000000001, -167.0685>, <99.3775, -166.358>, <99.3775, -165.481>//circle
				<99.3775, -165.481>, <99.3775, -164.60399999999998>, <100.08800000000001, -163.8935>, <100.965, -163.8935>//circle
				<100.965, -52.13349999999999>, <101.842, -52.13349999999999>, <102.55250000000001, -52.843999999999994>, <102.55250000000001, -53.721>//circle
				<102.55250000000001, -53.721>, <102.55250000000001, -54.598>, <101.842, -55.3085>, <100.965, -55.3085>//circle
				<100.965, -55.3085>, <100.08800000000001, -55.3085>, <99.3775, -54.598>, <99.3775, -53.721>//circle
				<99.3775, -53.721>, <99.3775, -52.843999999999994>, <100.08800000000001, -52.13349999999999>, <100.965, -52.13349999999999>//circle
				<128.397, -163.8935>, <129.274, -163.8935>, <129.9845, -164.60399999999998>, <129.9845, -165.481>//circle
				<129.9845, -165.481>, <129.9845, -166.358>, <129.274, -167.0685>, <128.397, -167.0685>//circle
				<128.397, -167.0685>, <127.52, -167.0685>, <126.80949999999999, -166.358>, <126.80949999999999, -165.481>//circle
				<126.80949999999999, -165.481>, <126.80949999999999, -164.60399999999998>, <127.52, -163.8935>, <128.397, -163.8935>//circle
				<128.397, -52.13349999999999>, <129.274, -52.13349999999999>, <129.9845, -52.843999999999994>, <129.9845, -53.721>//circle
				<129.9845, -53.721>, <129.9845, -54.598>, <129.274, -55.3085>, <128.397, -55.3085>//circle
				<128.397, -55.3085>, <127.52, -55.3085>, <126.80949999999999, -54.598>, <126.80949999999999, -53.721>//circle
				<126.80949999999999, -53.721>, <126.80949999999999, -52.843999999999994>, <127.52, -52.13349999999999>, <128.397, -52.13349999999999>//circle
				<100.965, -158.8135>, <101.842, -158.8135>, <102.55250000000001, -159.524>, <102.55250000000001, -160.401>//circle
				<102.55250000000001, -160.401>, <102.55250000000001, -161.27800000000002>, <101.842, -161.98850000000002>, <100.965, -161.98850000000002>//circle
				<100.965, -161.98850000000002>, <100.08800000000001, -161.98850000000002>, <99.3775, -161.27800000000002>, <99.3775, -160.401>//circle
				<99.3775, -160.401>, <99.3775, -159.524>, <100.08800000000001, -158.8135>, <100.965, -158.8135>//circle
				<100.965, -47.05349999999999>, <101.842, -47.05349999999999>, <102.55250000000001, -47.763999999999996>, <102.55250000000001, -48.641>//circle
				<102.55250000000001, -48.641>, <102.55250000000001, -49.518>, <101.842, -50.228500000000004>, <100.965, -50.228500000000004>//circle
				<100.965, -50.228500000000004>, <100.08800000000001, -50.228500000000004>, <99.3775, -49.518>, <99.3775, -48.641>//circle
				<99.3775, -48.641>, <99.3775, -47.763999999999996>, <100.08800000000001, -47.05349999999999>, <100.965, -47.05349999999999>//circle
				<128.397, -158.8135>, <129.274, -158.8135>, <129.9845, -159.524>, <129.9845, -160.401>//circle
				<129.9845, -160.401>, <129.9845, -161.27800000000002>, <129.274, -161.98850000000002>, <128.397, -161.98850000000002>//circle
				<128.397, -161.98850000000002>, <127.52, -161.98850000000002>, <126.80949999999999, -161.27800000000002>, <126.80949999999999, -160.401>//circle
				<126.80949999999999, -160.401>, <126.80949999999999, -159.524>, <127.52, -158.8135>, <128.397, -158.8135>//circle
				<128.397, -47.05349999999999>, <129.274, -47.05349999999999>, <129.9845, -47.763999999999996>, <129.9845, -48.641>//circle
				<129.9845, -48.641>, <129.9845, -49.518>, <129.274, -50.228500000000004>, <128.397, -50.228500000000004>//circle
				<128.397, -50.228500000000004>, <127.52, -50.228500000000004>, <126.80949999999999, -49.518>, <126.80949999999999, -48.641>//circle
				<126.80949999999999, -48.641>, <126.80949999999999, -47.763999999999996>, <127.52, -47.05349999999999>, <128.397, -47.05349999999999>//circle
				<106.045, -158.8135>, <106.922, -158.8135>, <107.63250000000001, -159.524>, <107.63250000000001, -160.401>//circle
				<107.63250000000001, -160.401>, <107.63250000000001, -161.27800000000002>, <106.922, -161.98850000000002>, <106.045, -161.98850000000002>//circle
				<106.045, -161.98850000000002>, <105.168, -161.98850000000002>, <104.4575, -161.27800000000002>, <104.4575, -160.401>//circle
				<104.4575, -160.401>, <104.4575, -159.524>, <105.168, -158.8135>, <106.045, -158.8135>//circle
				<106.045, -47.05349999999999>, <106.922, -47.05349999999999>, <107.63250000000001, -47.763999999999996>, <107.63250000000001, -48.641>//circle
				<107.63250000000001, -48.641>, <107.63250000000001, -49.518>, <106.922, -50.228500000000004>, <106.045, -50.228500000000004>//circle
				<106.045, -50.228500000000004>, <105.168, -50.228500000000004>, <104.4575, -49.518>, <104.4575, -48.641>//circle
				<104.4575, -48.641>, <104.4575, -47.763999999999996>, <105.168, -47.05349999999999>, <106.045, -47.05349999999999>//circle
				<133.477, -158.8135>, <134.354, -158.8135>, <135.0645, -159.524>, <135.0645, -160.401>//circle
				<135.0645, -160.401>, <135.0645, -161.27800000000002>, <134.354, -161.98850000000002>, <133.477, -161.98850000000002>//circle
				<133.477, -161.98850000000002>, <132.6, -161.98850000000002>, <131.8895, -161.27800000000002>, <131.8895, -160.401>//circle
				<131.8895, -160.401>, <131.8895, -159.524>, <132.6, -158.8135>, <133.477, -158.8135>//circle
				<133.477, -47.05349999999999>, <134.354, -47.05349999999999>, <135.0645, -47.763999999999996>, <135.0645, -48.641>//circle
				<135.0645, -48.641>, <135.0645, -49.518>, <134.354, -50.228500000000004>, <133.477, -50.228500000000004>//circle
				<133.477, -50.228500000000004>, <132.6, -50.228500000000004>, <131.8895, -49.518>, <131.8895, -48.641>//circle
				<131.8895, -48.641>, <131.8895, -47.763999999999996>, <132.6, -47.05349999999999>, <133.477, -47.05349999999999>//circle
				<111.125, -158.8135>, <112.002, -158.8135>, <112.7125, -159.524>, <112.7125, -160.401>//circle
				<112.7125, -160.401>, <112.7125, -161.27800000000002>, <112.002, -161.98850000000002>, <111.125, -161.98850000000002>//circle
				<111.125, -161.98850000000002>, <110.248, -161.98850000000002>, <109.5375, -161.27800000000002>, <109.5375, -160.401>//circle
				<109.5375, -160.401>, <109.5375, -159.524>, <110.248, -158.8135>, <111.125, -158.8135>//circle
				<111.125, -47.05349999999999>, <112.002, -47.05349999999999>, <112.7125, -47.763999999999996>, <112.7125, -48.641>//circle
				<112.7125, -48.641>, <112.7125, -49.518>, <112.002, -50.228500000000004>, <111.125, -50.228500000000004>//circle
				<111.125, -50.228500000000004>, <110.248, -50.228500000000004>, <109.5375, -49.518>, <109.5375, -48.641>//circle
				<109.5375, -48.641>, <109.5375, -47.763999999999996>, <110.248, -47.05349999999999>, <111.125, -47.05349999999999>//circle
				<138.557, -158.8135>, <139.434, -158.8135>, <140.1445, -159.524>, <140.1445, -160.401>//circle
				<140.1445, -160.401>, <140.1445, -161.27800000000002>, <139.434, -161.98850000000002>, <138.557, -161.98850000000002>//circle
				<138.557, -161.98850000000002>, <137.67999999999998, -161.98850000000002>, <136.96949999999998, -161.27800000000002>, <136.96949999999998, -160.401>//circle
				<136.96949999999998, -160.401>, <136.96949999999998, -159.524>, <137.67999999999998, -158.8135>, <138.557, -158.8135>//circle
				<138.557, -47.05349999999999>, <139.434, -47.05349999999999>, <140.1445, -47.763999999999996>, <140.1445, -48.641>//circle
				<140.1445, -48.641>, <140.1445, -49.518>, <139.434, -50.228500000000004>, <138.557, -50.228500000000004>//circle
				<138.557, -50.228500000000004>, <137.67999999999998, -50.228500000000004>, <136.96949999999998, -49.518>, <136.96949999999998, -48.641>//circle
				<136.96949999999998, -48.641>, <136.96949999999998, -47.763999999999996>, <137.67999999999998, -47.05349999999999>, <138.557, -47.05349999999999>//circle
				<226.441, -117.1575>, <227.879, -117.1575>, <229.0445, -118.323>, <229.0445, -119.761>//circle
				<229.0445, -119.761>, <229.0445, -121.199>, <227.879, -122.36449999999999>, <226.441, -122.36449999999999>//circle
				<226.441, -122.36449999999999>, <225.00300000000001, -122.36449999999999>, <223.8375, -121.199>, <223.8375, -119.761>//circle
				<223.8375, -119.761>, <223.8375, -118.323>, <225.00300000000001, -117.1575>, <226.441, -117.1575>//circle
				<225.857, -106.0065>, <227.295, -106.0065>, <228.4605, -107.172>, <228.4605, -108.61>//circle
				<228.4605, -108.61>, <228.4605, -110.048>, <227.295, -111.2135>, <225.857, -111.2135>//circle
				<225.857, -111.2135>, <224.419, -111.2135>, <223.2535, -110.048>, <223.2535, -108.61>//circle
				<223.2535, -108.61>, <223.2535, -107.172>, <224.419, -106.0065>, <225.857, -106.0065>//circle
				<224.11, -94.9775>, <225.548, -94.9775>, <226.7135, -96.143>, <226.7135, -97.581>//circle
				<226.7135, -97.581>, <226.7135, -99.019>, <225.548, -100.1845>, <224.11, -100.1845>//circle
				<224.11, -100.1845>, <222.67200000000003, -100.1845>, <221.50650000000002, -99.019>, <221.50650000000002, -97.581>//circle
				<221.50650000000002, -97.581>, <221.50650000000002, -96.143>, <222.67200000000003, -94.9775>, <224.11, -94.9775>//circle
				<221.22, -84.1915>, <222.658, -84.1915>, <223.8235, -85.357>, <223.8235, -86.795>//circle
				<223.8235, -86.795>, <223.8235, -88.233>, <222.658, -89.3985>, <221.22, -89.3985>//circle
				<221.22, -89.3985>, <219.782, -89.3985>, <218.6165, -88.233>, <218.6165, -86.795>//circle
				<218.6165, -86.795>, <218.6165, -85.357>, <219.782, -84.1915>, <221.22, -84.1915>//circle
				<217.218, -73.76650000000001>, <218.65599999999998, -73.76650000000001>, <219.8215, -74.932>, <219.8215, -76.37>//circle
				<219.8215, -76.37>, <219.8215, -77.808>, <218.65599999999998, -78.9735>, <217.218, -78.9735>//circle
				<217.218, -78.9735>, <215.78, -78.9735>, <214.6145, -77.808>, <214.6145, -76.37>//circle
				<214.6145, -76.37>, <214.6145, -74.932>, <215.78, -73.76650000000001>, <217.218, -73.76650000000001>//circle
				<212.149, -63.81750000000001>, <213.587, -63.81750000000001>, <214.7525, -64.983>, <214.7525, -66.421>//circle
				<214.7525, -66.421>, <214.7525, -67.85900000000001>, <213.587, -69.0245>, <212.149, -69.0245>//circle
				<212.149, -69.0245>, <210.711, -69.0245>, <209.5455, -67.85900000000001>, <209.5455, -66.421>//circle
				<209.5455, -66.421>, <209.5455, -64.983>, <210.711, -63.81750000000001>, <212.149, -63.81750000000001>//circle
				<206.067, -54.4525>, <207.505, -54.4525>, <208.6705, -55.617999999999995>, <208.6705, -57.056>//circle
				<208.6705, -57.056>, <208.6705, -58.494>, <207.505, -59.659499999999994>, <206.067, -59.659499999999994>//circle
				<206.067, -59.659499999999994>, <204.62900000000002, -59.659499999999994>, <203.4635, -58.494>, <203.4635, -57.056>//circle
				<203.4635, -57.056>, <203.4635, -55.617999999999995>, <204.62900000000002, -54.4525>, <206.067, -54.4525>//circle
				<199.04, -45.7745>, <200.47799999999998, -45.7745>, <201.6435, -46.94>, <201.6435, -48.378>//circle
				<201.6435, -48.378>, <201.6435, -49.816>, <200.47799999999998, -50.9815>, <199.04, -50.9815>//circle
				<199.04, -50.9815>, <197.602, -50.9815>, <196.4365, -49.816>, <196.4365, -48.378>//circle
				<196.4365, -48.378>, <196.4365, -46.94>, <197.602, -45.7745>, <199.04, -45.7745>//circle
				<191.144, -37.8785>, <192.582, -37.8785>, <193.7475, -39.044>, <193.7475, -40.482>//circle
				<193.7475, -40.482>, <193.7475, -41.92>, <192.582, -43.085499999999996>, <191.144, -43.085499999999996>//circle
				<191.144, -43.085499999999996>, <189.70600000000002, -43.085499999999996>, <188.5405, -41.92>, <188.5405, -40.482>//circle
				<188.5405, -40.482>, <188.5405, -39.044>, <189.70600000000002, -37.8785>, <191.144, -37.8785>//circle
				<182.466, -30.8515>, <183.904, -30.8515>, <185.0695, -32.016999999999996>, <185.0695, -33.455>//circle
				<185.0695, -33.455>, <185.0695, -34.893>, <183.904, -36.058499999999995>, <182.466, -36.058499999999995>//circle
				<182.466, -36.058499999999995>, <181.02800000000002, -36.058499999999995>, <179.8625, -34.893>, <179.8625, -33.455>//circle
				<179.8625, -33.455>, <179.8625, -32.016999999999996>, <181.02800000000002, -30.8515>, <182.466, -30.8515>//circle
				<173.101, -24.769500000000004>, <174.539, -24.769500000000004>, <175.7045, -25.935000000000002>, <175.7045, -27.373>//circle
				<175.7045, -27.373>, <175.7045, -28.811>, <174.539, -29.976499999999998>, <173.101, -29.976499999999998>//circle
				<173.101, -29.976499999999998>, <171.663, -29.976499999999998>, <170.4975, -28.811>, <170.4975, -27.373>//circle
				<170.4975, -27.373>, <170.4975, -25.935000000000002>, <171.663, -24.769500000000004>, <173.101, -24.769500000000004>//circle
				<163.152, -19.7005>, <164.58999999999997, -19.7005>, <165.75549999999998, -20.866>, <165.75549999999998, -22.304>//circle
				<165.75549999999998, -22.304>, <165.75549999999998, -23.741999999999997>, <164.58999999999997, -24.907499999999995>, <163.152, -24.907499999999995>//circle
				<163.152, -24.907499999999995>, <161.714, -24.907499999999995>, <160.5485, -23.741999999999997>, <160.5485, -22.304>//circle
				<160.5485, -22.304>, <160.5485, -20.866>, <161.714, -19.7005>, <163.152, -19.7005>//circle
				<152.727, -15.698500000000003>, <154.165, -15.698500000000003>, <155.3305, -16.864>, <155.3305, -18.302>//circle
				<155.3305, -18.302>, <155.3305, -19.74>, <154.165, -20.905499999999996>, <152.727, -20.905499999999996>//circle
				<152.727, -20.905499999999996>, <151.28900000000002, -20.905499999999996>, <150.1235, -19.74>, <150.1235, -18.302>//circle
				<150.1235, -18.302>, <150.1235, -16.864>, <151.28900000000002, -15.698500000000003>, <152.727, -15.698500000000003>//circle
				<141.941, -12.808500000000004>, <143.379, -12.808500000000004>, <144.5445, -13.974>, <144.5445, -15.412>//circle
				<144.5445, -15.412>, <144.5445, -16.85>, <143.379, -18.015499999999996>, <141.941, -18.015499999999996>//circle
				<141.941, -18.015499999999996>, <140.50300000000001, -18.015499999999996>, <139.3375, -16.85>, <139.3375, -15.412>//circle
				<139.3375, -15.412>, <139.3375, -13.974>, <140.50300000000001, -12.808500000000004>, <141.941, -12.808500000000004>//circle
				<130.912, -11.061500000000002>, <132.35, -11.061500000000002>, <133.5155, -12.226999999999999>, <133.5155, -13.665>//circle
				<133.5155, -13.665>, <133.5155, -15.103>, <132.35, -16.268499999999996>, <130.912, -16.268499999999996>//circle
				<130.912, -16.268499999999996>, <129.47400000000002, -16.268499999999996>, <128.3085, -15.103>, <128.3085, -13.665>//circle
				<128.3085, -13.665>, <128.3085, -12.226999999999999>, <129.47400000000002, -11.061500000000002>, <130.912, -11.061500000000002>//circle
				<119.761, -10.477500000000003>, <121.199, -10.477500000000003>, <122.36449999999999, -11.642999999999999>, <122.36449999999999, -13.081>//circle
				<122.36449999999999, -13.081>, <122.36449999999999, -14.519>, <121.199, -15.684499999999996>, <119.761, -15.684499999999996>//circle
				<119.761, -15.684499999999996>, <118.323, -15.684499999999996>, <117.1575, -14.519>, <117.1575, -13.081>//circle
				<117.1575, -13.081>, <117.1575, -11.642999999999999>, <118.323, -10.477500000000003>, <119.761, -10.477500000000003>//circle
				<108.61, -11.061500000000002>, <110.048, -11.061500000000002>, <111.2135, -12.226999999999999>, <111.2135, -13.665>//circle
				<111.2135, -13.665>, <111.2135, -15.103>, <110.048, -16.268499999999996>, <108.61, -16.268499999999996>//circle
				<108.61, -16.268499999999996>, <107.172, -16.268499999999996>, <106.0065, -15.103>, <106.0065, -13.665>//circle
				<106.0065, -13.665>, <106.0065, -12.226999999999999>, <107.172, -11.061500000000002>, <108.61, -11.061500000000002>//circle
				<97.581, -12.808500000000004>, <99.019, -12.808500000000004>, <100.1845, -13.974>, <100.1845, -15.412>//circle
				<100.1845, -15.412>, <100.1845, -16.85>, <99.019, -18.015499999999996>, <97.581, -18.015499999999996>//circle
				<97.581, -18.015499999999996>, <96.143, -18.015499999999996>, <94.9775, -16.85>, <94.9775, -15.412>//circle
				<94.9775, -15.412>, <94.9775, -13.974>, <96.143, -12.808500000000004>, <97.581, -12.808500000000004>//circle
				<86.795, -15.698500000000003>, <88.233, -15.698500000000003>, <89.3985, -16.864>, <89.3985, -18.302>//circle
				<89.3985, -18.302>, <89.3985, -19.74>, <88.233, -20.905499999999996>, <86.795, -20.905499999999996>//circle
				<86.795, -20.905499999999996>, <85.357, -20.905499999999996>, <84.1915, -19.74>, <84.1915, -18.302>//circle
				<84.1915, -18.302>, <84.1915, -16.864>, <85.357, -15.698500000000003>, <86.795, -15.698500000000003>//circle
				<76.37, -19.7005>, <77.808, -19.7005>, <78.9735, -20.866>, <78.9735, -22.304>//circle
				<78.9735, -22.304>, <78.9735, -23.741999999999997>, <77.808, -24.907499999999995>, <76.37, -24.907499999999995>//circle
				<76.37, -24.907499999999995>, <74.932, -24.907499999999995>, <73.76650000000001, -23.741999999999997>, <73.76650000000001, -22.304>//circle
				<73.76650000000001, -22.304>, <73.76650000000001, -20.866>, <74.932, -19.7005>, <76.37, -19.7005>//circle
				<66.421, -24.769500000000004>, <67.85900000000001, -24.769500000000004>, <69.0245, -25.935000000000002>, <69.0245, -27.373>//circle
				<69.0245, -27.373>, <69.0245, -28.811>, <67.85900000000001, -29.976499999999998>, <66.421, -29.976499999999998>//circle
				<66.421, -29.976499999999998>, <64.983, -29.976499999999998>, <63.81750000000001, -28.811>, <63.81750000000001, -27.373>//circle
				<63.81750000000001, -27.373>, <63.81750000000001, -25.935000000000002>, <64.983, -24.769500000000004>, <66.421, -24.769500000000004>//circle
				<57.056, -30.8515>, <58.494, -30.8515>, <59.659499999999994, -32.016999999999996>, <59.659499999999994, -33.455>//circle
				<59.659499999999994, -33.455>, <59.659499999999994, -34.893>, <58.494, -36.058499999999995>, <57.056, -36.058499999999995>//circle
				<57.056, -36.058499999999995>, <55.617999999999995, -36.058499999999995>, <54.4525, -34.893>, <54.4525, -33.455>//circle
				<54.4525, -33.455>, <54.4525, -32.016999999999996>, <55.617999999999995, -30.8515>, <57.056, -30.8515>//circle
				<48.378, -37.8785>, <49.816, -37.8785>, <50.9815, -39.044>, <50.9815, -40.482>//circle
				<50.9815, -40.482>, <50.9815, -41.92>, <49.816, -43.085499999999996>, <48.378, -43.085499999999996>//circle
				<48.378, -43.085499999999996>, <46.94, -43.085499999999996>, <45.7745, -41.92>, <45.7745, -40.482>//circle
				<45.7745, -40.482>, <45.7745, -39.044>, <46.94, -37.8785>, <48.378, -37.8785>//circle
				<40.482, -45.7745>, <41.92, -45.7745>, <43.085499999999996, -46.94>, <43.085499999999996, -48.378>//circle
				<43.085499999999996, -48.378>, <43.085499999999996, -49.816>, <41.92, -50.9815>, <40.482, -50.9815>//circle
				<40.482, -50.9815>, <39.044, -50.9815>, <37.8785, -49.816>, <37.8785, -48.378>//circle
				<37.8785, -48.378>, <37.8785, -46.94>, <39.044, -45.7745>, <40.482, -45.7745>//circle
				<33.455, -54.4525>, <34.893, -54.4525>, <36.058499999999995, -55.617999999999995>, <36.058499999999995, -57.056>//circle
				<36.058499999999995, -57.056>, <36.058499999999995, -58.494>, <34.893, -59.659499999999994>, <33.455, -59.659499999999994>//circle
				<33.455, -59.659499999999994>, <32.016999999999996, -59.659499999999994>, <30.8515, -58.494>, <30.8515, -57.056>//circle
				<30.8515, -57.056>, <30.8515, -55.617999999999995>, <32.016999999999996, -54.4525>, <33.455, -54.4525>//circle
				<27.373, -63.81750000000001>, <28.811, -63.81750000000001>, <29.9765, -64.983>, <29.9765, -66.421>//circle
				<29.9765, -66.421>, <29.9765, -67.85900000000001>, <28.811, -69.0245>, <27.373, -69.0245>//circle
				<27.373, -69.0245>, <25.935000000000002, -69.0245>, <24.7695, -67.85900000000001>, <24.7695, -66.421>//circle
				<24.7695, -66.421>, <24.7695, -64.983>, <25.935000000000002, -63.81750000000001>, <27.373, -63.81750000000001>//circle
				<22.304, -73.76650000000001>, <23.741999999999997, -73.76650000000001>, <24.9075, -74.932>, <24.9075, -76.37>//circle
				<24.9075, -76.37>, <24.9075, -77.808>, <23.741999999999997, -78.9735>, <22.304, -78.9735>//circle
				<22.304, -78.9735>, <20.866, -78.9735>, <19.700499999999998, -77.808>, <19.700499999999998, -76.37>//circle
				<19.700499999999998, -76.37>, <19.700499999999998, -74.932>, <20.866, -73.76650000000001>, <22.304, -73.76650000000001>//circle
				<18.302, -84.1915>, <19.74, -84.1915>, <20.9055, -85.357>, <20.9055, -86.795>//circle
				<20.9055, -86.795>, <20.9055, -88.233>, <19.74, -89.3985>, <18.302, -89.3985>//circle
				<18.302, -89.3985>, <16.864, -89.3985>, <15.6985, -88.233>, <15.6985, -86.795>//circle
				<15.6985, -86.795>, <15.6985, -85.357>, <16.864, -84.1915>, <18.302, -84.1915>//circle
				<15.412, -94.9775>, <16.85, -94.9775>, <18.0155, -96.143>, <18.0155, -97.581>//circle
				<18.0155, -97.581>, <18.0155, -99.019>, <16.85, -100.1845>, <15.412, -100.1845>//circle
				<15.412, -100.1845>, <13.974, -100.1845>, <12.808500000000002, -99.019>, <12.808500000000002, -97.581>//circle
				<12.808500000000002, -97.581>, <12.808500000000002, -96.143>, <13.974, -94.9775>, <15.412, -94.9775>//circle
				<13.665, -106.0065>, <15.103, -106.0065>, <16.2685, -107.172>, <16.2685, -108.61>//circle
				<16.2685, -108.61>, <16.2685, -110.048>, <15.103, -111.2135>, <13.665, -111.2135>//circle
				<13.665, -111.2135>, <12.226999999999999, -111.2135>, <11.061499999999999, -110.048>, <11.061499999999999, -108.61>//circle
				<11.061499999999999, -108.61>, <11.061499999999999, -107.172>, <12.226999999999999, -106.0065>, <13.665, -106.0065>//circle
				<13.081, -117.1575>, <14.519, -117.1575>, <15.6845, -118.323>, <15.6845, -119.761>//circle
				<15.6845, -119.761>, <15.6845, -121.199>, <14.519, -122.36449999999999>, <13.081, -122.36449999999999>//circle
				<13.081, -122.36449999999999>, <11.642999999999999, -122.36449999999999>, <10.4775, -121.199>, <10.4775, -119.761>//circle
				<10.4775, -119.761>, <10.4775, -118.323>, <11.642999999999999, -117.1575>, <13.081, -117.1575>//circle
				<13.665, -128.3085>, <15.103, -128.3085>, <16.2685, -129.47400000000002>, <16.2685, -130.912>//circle
				<16.2685, -130.912>, <16.2685, -132.35>, <15.103, -133.5155>, <13.665, -133.5155>//circle
				<13.665, -133.5155>, <12.226999999999999, -133.5155>, <11.061499999999999, -132.35>, <11.061499999999999, -130.912>//circle
				<11.061499999999999, -130.912>, <11.061499999999999, -129.47400000000002>, <12.226999999999999, -128.3085>, <13.665, -128.3085>//circle
				<15.412, -139.3375>, <16.85, -139.3375>, <18.0155, -140.50300000000001>, <18.0155, -141.941>//circle
				<18.0155, -141.941>, <18.0155, -143.379>, <16.85, -144.5445>, <15.412, -144.5445>//circle
				<15.412, -144.5445>, <13.974, -144.5445>, <12.808500000000002, -143.379>, <12.808500000000002, -141.941>//circle
				<12.808500000000002, -141.941>, <12.808500000000002, -140.50300000000001>, <13.974, -139.3375>, <15.412, -139.3375>//circle
				<18.302, -150.1235>, <19.74, -150.1235>, <20.9055, -151.28900000000002>, <20.9055, -152.727>//circle
				<20.9055, -152.727>, <20.9055, -154.165>, <19.74, -155.3305>, <18.302, -155.3305>//circle
				<18.302, -155.3305>, <16.864, -155.3305>, <15.6985, -154.165>, <15.6985, -152.727>//circle
				<15.6985, -152.727>, <15.6985, -151.28900000000002>, <16.864, -150.1235>, <18.302, -150.1235>//circle
				<22.304, -160.5485>, <23.741999999999997, -160.5485>, <24.9075, -161.714>, <24.9075, -163.152>//circle
				<24.9075, -163.152>, <24.9075, -164.58999999999997>, <23.741999999999997, -165.75549999999998>, <22.304, -165.75549999999998>//circle
				<22.304, -165.75549999999998>, <20.866, -165.75549999999998>, <19.700499999999998, -164.58999999999997>, <19.700499999999998, -163.152>//circle
				<19.700499999999998, -163.152>, <19.700499999999998, -161.714>, <20.866, -160.5485>, <22.304, -160.5485>//circle
				<27.373, -170.4975>, <28.811, -170.4975>, <29.9765, -171.663>, <29.9765, -173.101>//circle
				<29.9765, -173.101>, <29.9765, -174.539>, <28.811, -175.7045>, <27.373, -175.7045>//circle
				<27.373, -175.7045>, <25.935000000000002, -175.7045>, <24.7695, -174.539>, <24.7695, -173.101>//circle
				<24.7695, -173.101>, <24.7695, -171.663>, <25.935000000000002, -170.4975>, <27.373, -170.4975>//circle
				<33.455, -179.8625>, <34.893, -179.8625>, <36.058499999999995, -181.02800000000002>, <36.058499999999995, -182.466>//circle
				<36.058499999999995, -182.466>, <36.058499999999995, -183.904>, <34.893, -185.0695>, <33.455, -185.0695>//circle
				<33.455, -185.0695>, <32.016999999999996, -185.0695>, <30.8515, -183.904>, <30.8515, -182.466>//circle
				<30.8515, -182.466>, <30.8515, -181.02800000000002>, <32.016999999999996, -179.8625>, <33.455, -179.8625>//circle
				<40.482, -188.5405>, <41.92, -188.5405>, <43.085499999999996, -189.70600000000002>, <43.085499999999996, -191.144>//circle
				<43.085499999999996, -191.144>, <43.085499999999996, -192.582>, <41.92, -193.7475>, <40.482, -193.7475>//circle
				<40.482, -193.7475>, <39.044, -193.7475>, <37.8785, -192.582>, <37.8785, -191.144>//circle
				<37.8785, -191.144>, <37.8785, -189.70600000000002>, <39.044, -188.5405>, <40.482, -188.5405>//circle
				<48.378, -196.4365>, <49.816, -196.4365>, <50.9815, -197.602>, <50.9815, -199.04>//circle
				<50.9815, -199.04>, <50.9815, -200.47799999999998>, <49.816, -201.6435>, <48.378, -201.6435>//circle
				<48.378, -201.6435>, <46.94, -201.6435>, <45.7745, -200.47799999999998>, <45.7745, -199.04>//circle
				<45.7745, -199.04>, <45.7745, -197.602>, <46.94, -196.4365>, <48.378, -196.4365>//circle
				<57.056, -203.4635>, <58.494, -203.4635>, <59.659499999999994, -204.62900000000002>, <59.659499999999994, -206.067>//circle
				<59.659499999999994, -206.067>, <59.659499999999994, -207.505>, <58.494, -208.6705>, <57.056, -208.6705>//circle
				<57.056, -208.6705>, <55.617999999999995, -208.6705>, <54.4525, -207.505>, <54.4525, -206.067>//circle
				<54.4525, -206.067>, <54.4525, -204.62900000000002>, <55.617999999999995, -203.4635>, <57.056, -203.4635>//circle
				<66.421, -209.5455>, <67.85900000000001, -209.5455>, <69.0245, -210.711>, <69.0245, -212.149>//circle
				<69.0245, -212.149>, <69.0245, -213.587>, <67.85900000000001, -214.7525>, <66.421, -214.7525>//circle
				<66.421, -214.7525>, <64.983, -214.7525>, <63.81750000000001, -213.587>, <63.81750000000001, -212.149>//circle
				<63.81750000000001, -212.149>, <63.81750000000001, -210.711>, <64.983, -209.5455>, <66.421, -209.5455>//circle
				<76.37, -214.6145>, <77.808, -214.6145>, <78.9735, -215.78>, <78.9735, -217.218>//circle
				<78.9735, -217.218>, <78.9735, -218.65599999999998>, <77.808, -219.8215>, <76.37, -219.8215>//circle
				<76.37, -219.8215>, <74.932, -219.8215>, <73.76650000000001, -218.65599999999998>, <73.76650000000001, -217.218>//circle
				<73.76650000000001, -217.218>, <73.76650000000001, -215.78>, <74.932, -214.6145>, <76.37, -214.6145>//circle
				<86.795, -218.6165>, <88.233, -218.6165>, <89.3985, -219.782>, <89.3985, -221.22>//circle
				<89.3985, -221.22>, <89.3985, -222.658>, <88.233, -223.8235>, <86.795, -223.8235>//circle
				<86.795, -223.8235>, <85.357, -223.8235>, <84.1915, -222.658>, <84.1915, -221.22>//circle
				<84.1915, -221.22>, <84.1915, -219.782>, <85.357, -218.6165>, <86.795, -218.6165>//circle
				<97.581, -221.50650000000002>, <99.019, -221.50650000000002>, <100.1845, -222.67200000000003>, <100.1845, -224.11>//circle
				<100.1845, -224.11>, <100.1845, -225.548>, <99.019, -226.7135>, <97.581, -226.7135>//circle
				<97.581, -226.7135>, <96.143, -226.7135>, <94.9775, -225.548>, <94.9775, -224.11>//circle
				<94.9775, -224.11>, <94.9775, -222.67200000000003>, <96.143, -221.50650000000002>, <97.581, -221.50650000000002>//circle
				<108.61, -223.2535>, <110.048, -223.2535>, <111.2135, -224.419>, <111.2135, -225.857>//circle
				<111.2135, -225.857>, <111.2135, -227.295>, <110.048, -228.4605>, <108.61, -228.4605>//circle
				<108.61, -228.4605>, <107.172, -228.4605>, <106.0065, -227.295>, <106.0065, -225.857>//circle
				<106.0065, -225.857>, <106.0065, -224.419>, <107.172, -223.2535>, <108.61, -223.2535>//circle
				<119.761, -223.8375>, <121.199, -223.8375>, <122.36449999999999, -225.00300000000001>, <122.36449999999999, -226.441>//circle
				<122.36449999999999, -226.441>, <122.36449999999999, -227.879>, <121.199, -229.0445>, <119.761, -229.0445>//circle
				<119.761, -229.0445>, <118.323, -229.0445>, <117.1575, -227.879>, <117.1575, -226.441>//circle
				<117.1575, -226.441>, <117.1575, -225.00300000000001>, <118.323, -223.8375>, <119.761, -223.8375>//circle
				<130.912, -223.2535>, <132.35, -223.2535>, <133.5155, -224.419>, <133.5155, -225.857>//circle
				<133.5155, -225.857>, <133.5155, -227.295>, <132.35, -228.4605>, <130.912, -228.4605>//circle
				<130.912, -228.4605>, <129.47400000000002, -228.4605>, <128.3085, -227.295>, <128.3085, -225.857>//circle
				<128.3085, -225.857>, <128.3085, -224.419>, <129.47400000000002, -223.2535>, <130.912, -223.2535>//circle
				<141.941, -221.50650000000002>, <143.379, -221.50650000000002>, <144.5445, -222.67200000000003>, <144.5445, -224.11>//circle
				<144.5445, -224.11>, <144.5445, -225.548>, <143.379, -226.7135>, <141.941, -226.7135>//circle
				<141.941, -226.7135>, <140.50300000000001, -226.7135>, <139.3375, -225.548>, <139.3375, -224.11>//circle
				<139.3375, -224.11>, <139.3375, -222.67200000000003>, <140.50300000000001, -221.50650000000002>, <141.941, -221.50650000000002>//circle
				<152.727, -218.6165>, <154.165, -218.6165>, <155.3305, -219.782>, <155.3305, -221.22>//circle
				<155.3305, -221.22>, <155.3305, -222.658>, <154.165, -223.8235>, <152.727, -223.8235>//circle
				<152.727, -223.8235>, <151.28900000000002, -223.8235>, <150.1235, -222.658>, <150.1235, -221.22>//circle
				<150.1235, -221.22>, <150.1235, -219.782>, <151.28900000000002, -218.6165>, <152.727, -218.6165>//circle
				<163.152, -214.6145>, <164.58999999999997, -214.6145>, <165.75549999999998, -215.78>, <165.75549999999998, -217.218>//circle
				<165.75549999999998, -217.218>, <165.75549999999998, -218.65599999999998>, <164.58999999999997, -219.8215>, <163.152, -219.8215>//circle
				<163.152, -219.8215>, <161.714, -219.8215>, <160.5485, -218.65599999999998>, <160.5485, -217.218>//circle
				<160.5485, -217.218>, <160.5485, -215.78>, <161.714, -214.6145>, <163.152, -214.6145>//circle
				<173.101, -209.5455>, <174.539, -209.5455>, <175.7045, -210.711>, <175.7045, -212.149>//circle
				<175.7045, -212.149>, <175.7045, -213.587>, <174.539, -214.7525>, <173.101, -214.7525>//circle
				<173.101, -214.7525>, <171.663, -214.7525>, <170.4975, -213.587>, <170.4975, -212.149>//circle
				<170.4975, -212.149>, <170.4975, -210.711>, <171.663, -209.5455>, <173.101, -209.5455>//circle
				<182.466, -203.4635>, <183.904, -203.4635>, <185.0695, -204.62900000000002>, <185.0695, -206.067>//circle
				<185.0695, -206.067>, <185.0695, -207.505>, <183.904, -208.6705>, <182.466, -208.6705>//circle
				<182.466, -208.6705>, <181.02800000000002, -208.6705>, <179.8625, -207.505>, <179.8625, -206.067>//circle
				<179.8625, -206.067>, <179.8625, -204.62900000000002>, <181.02800000000002, -203.4635>, <182.466, -203.4635>//circle
				<191.144, -196.4365>, <192.582, -196.4365>, <193.7475, -197.602>, <193.7475, -199.04>//circle
				<193.7475, -199.04>, <193.7475, -200.47799999999998>, <192.582, -201.6435>, <191.144, -201.6435>//circle
				<191.144, -201.6435>, <189.70600000000002, -201.6435>, <188.5405, -200.47799999999998>, <188.5405, -199.04>//circle
				<188.5405, -199.04>, <188.5405, -197.602>, <189.70600000000002, -196.4365>, <191.144, -196.4365>//circle
				<199.04, -188.5405>, <200.47799999999998, -188.5405>, <201.6435, -189.70600000000002>, <201.6435, -191.144>//circle
				<201.6435, -191.144>, <201.6435, -192.582>, <200.47799999999998, -193.7475>, <199.04, -193.7475>//circle
				<199.04, -193.7475>, <197.602, -193.7475>, <196.4365, -192.582>, <196.4365, -191.144>//circle
				<196.4365, -191.144>, <196.4365, -189.70600000000002>, <197.602, -188.5405>, <199.04, -188.5405>//circle
				<206.067, -179.8625>, <207.505, -179.8625>, <208.6705, -181.02800000000002>, <208.6705, -182.466>//circle
				<208.6705, -182.466>, <208.6705, -183.904>, <207.505, -185.0695>, <206.067, -185.0695>//circle
				<206.067, -185.0695>, <204.62900000000002, -185.0695>, <203.4635, -183.904>, <203.4635, -182.466>//circle
				<203.4635, -182.466>, <203.4635, -181.02800000000002>, <204.62900000000002, -179.8625>, <206.067, -179.8625>//circle
				<212.149, -170.4975>, <213.587, -170.4975>, <214.7525, -171.663>, <214.7525, -173.101>//circle
				<214.7525, -173.101>, <214.7525, -174.539>, <213.587, -175.7045>, <212.149, -175.7045>//circle
				<212.149, -175.7045>, <210.711, -175.7045>, <209.5455, -174.539>, <209.5455, -173.101>//circle
				<209.5455, -173.101>, <209.5455, -171.663>, <210.711, -170.4975>, <212.149, -170.4975>//circle
				<217.218, -160.5485>, <218.65599999999998, -160.5485>, <219.8215, -161.714>, <219.8215, -163.152>//circle
				<219.8215, -163.152>, <219.8215, -164.58999999999997>, <218.65599999999998, -165.75549999999998>, <217.218, -165.75549999999998>//circle
				<217.218, -165.75549999999998>, <215.78, -165.75549999999998>, <214.6145, -164.58999999999997>, <214.6145, -163.152>//circle
				<214.6145, -163.152>, <214.6145, -161.714>, <215.78, -160.5485>, <217.218, -160.5485>//circle
				<221.22, -150.1235>, <222.658, -150.1235>, <223.8235, -151.28900000000002>, <223.8235, -152.727>//circle
				<223.8235, -152.727>, <223.8235, -154.165>, <222.658, -155.3305>, <221.22, -155.3305>//circle
				<221.22, -155.3305>, <219.782, -155.3305>, <218.6165, -154.165>, <218.6165, -152.727>//circle
				<218.6165, -152.727>, <218.6165, -151.28900000000002>, <219.782, -150.1235>, <221.22, -150.1235>//circle
				<224.11, -139.3375>, <225.548, -139.3375>, <226.7135, -140.50300000000001>, <226.7135, -141.941>//circle
				<226.7135, -141.941>, <226.7135, -143.379>, <225.548, -144.5445>, <224.11, -144.5445>//circle
				<224.11, -144.5445>, <222.67200000000003, -144.5445>, <221.50650000000002, -143.379>, <221.50650000000002, -141.941>//circle
				<221.50650000000002, -141.941>, <221.50650000000002, -140.50300000000001>, <222.67200000000003, -139.3375>, <224.11, -139.3375>//circle
				<225.857, -128.3085>, <227.295, -128.3085>, <228.4605, -129.47400000000002>, <228.4605, -130.912>//circle
				<228.4605, -130.912>, <228.4605, -132.35>, <227.295, -133.5155>, <225.857, -133.5155>//circle
				<225.857, -133.5155>, <224.419, -133.5155>, <223.2535, -132.35>, <223.2535, -130.912>//circle
				<223.2535, -130.912>, <223.2535, -129.47400000000002>, <224.419, -128.3085>, <225.857, -128.3085>//circle
				<218.821, -117.1575>, <220.259, -117.1575>, <221.4245, -118.323>, <221.4245, -119.761>//circle
				<221.4245, -119.761>, <221.4245, -121.199>, <220.259, -122.36449999999999>, <218.821, -122.36449999999999>//circle
				<218.821, -122.36449999999999>, <217.383, -122.36449999999999>, <216.2175, -121.199>, <216.2175, -119.761>//circle
				<216.2175, -119.761>, <216.2175, -118.323>, <217.383, -117.1575>, <218.821, -117.1575>//circle
				<205.549, -67.6275>, <206.987, -67.6275>, <208.1525, -68.79299999999999>, <208.1525, -70.231>//circle
				<208.1525, -70.231>, <208.1525, -71.669>, <206.987, -72.83449999999999>, <205.549, -72.83449999999999>//circle
				<205.549, -72.83449999999999>, <204.11100000000002, -72.83449999999999>, <202.9455, -71.669>, <202.9455, -70.231>//circle
				<202.9455, -70.231>, <202.9455, -68.79299999999999>, <204.11100000000002, -67.6275>, <205.549, -67.6275>//circle
				<169.291, -31.369500000000002>, <170.72899999999998, -31.369500000000002>, <171.8945, -32.535>, <171.8945, -33.973>//circle
				<171.8945, -33.973>, <171.8945, -35.411>, <170.72899999999998, -36.576499999999996>, <169.291, -36.576499999999996>//circle
				<169.291, -36.576499999999996>, <167.853, -36.576499999999996>, <166.6875, -35.411>, <166.6875, -33.973>//circle
				<166.6875, -33.973>, <166.6875, -32.535>, <167.853, -31.369500000000002>, <169.291, -31.369500000000002>//circle
				<119.761, -18.097500000000004>, <121.199, -18.097500000000004>, <122.36449999999999, -19.263>, <122.36449999999999, -20.701>//circle
				<122.36449999999999, -20.701>, <122.36449999999999, -22.139>, <121.199, -23.304499999999997>, <119.761, -23.304499999999997>//circle
				<119.761, -23.304499999999997>, <118.323, -23.304499999999997>, <117.1575, -22.139>, <117.1575, -20.701>//circle
				<117.1575, -20.701>, <117.1575, -19.263>, <118.323, -18.097500000000004>, <119.761, -18.097500000000004>//circle
				<70.231, -31.369500000000002>, <71.669, -31.369500000000002>, <72.83449999999999, -32.535>, <72.83449999999999, -33.973>//circle
				<72.83449999999999, -33.973>, <72.83449999999999, -35.411>, <71.669, -36.576499999999996>, <70.231, -36.576499999999996>//circle
				<70.231, -36.576499999999996>, <68.79299999999999, -36.576499999999996>, <67.6275, -35.411>, <67.6275, -33.973>//circle
				<67.6275, -33.973>, <67.6275, -32.535>, <68.79299999999999, -31.369500000000002>, <70.231, -31.369500000000002>//circle
				<33.973, -67.6275>, <35.411, -67.6275>, <36.576499999999996, -68.79299999999999>, <36.576499999999996, -70.231>//circle
				<36.576499999999996, -70.231>, <36.576499999999996, -71.669>, <35.411, -72.83449999999999>, <33.973, -72.83449999999999>//circle
				<33.973, -72.83449999999999>, <32.535, -72.83449999999999>, <31.369500000000002, -71.669>, <31.369500000000002, -70.231>//circle
				<31.369500000000002, -70.231>, <31.369500000000002, -68.79299999999999>, <32.535, -67.6275>, <33.973, -67.6275>//circle
				<20.701, -117.1575>, <22.139, -117.1575>, <23.3045, -118.323>, <23.3045, -119.761>//circle
				<23.3045, -119.761>, <23.3045, -121.199>, <22.139, -122.36449999999999>, <20.701, -122.36449999999999>//circle
				<20.701, -122.36449999999999>, <19.263, -122.36449999999999>, <18.0975, -121.199>, <18.0975, -119.761>//circle
				<18.0975, -119.761>, <18.0975, -118.323>, <19.263, -117.1575>, <20.701, -117.1575>//circle
				<49.911, -117.1575>, <51.349000000000004, -117.1575>, <52.5145, -118.323>, <52.5145, -119.761>//circle
				<52.5145, -119.761>, <52.5145, -121.199>, <51.349000000000004, -122.36449999999999>, <49.911, -122.36449999999999>//circle
				<49.911, -122.36449999999999>, <48.473, -122.36449999999999>, <47.307500000000005, -121.199>, <47.307500000000005, -119.761>//circle
				<47.307500000000005, -119.761>, <47.307500000000005, -118.323>, <48.473, -117.1575>, <49.911, -117.1575>//circle
				<62.611, -117.1575>, <64.04899999999999, -117.1575>, <65.21449999999999, -118.323>, <65.21449999999999, -119.761>//circle
				<65.21449999999999, -119.761>, <65.21449999999999, -121.199>, <64.04899999999999, -122.36449999999999>, <62.611, -122.36449999999999>//circle
				<62.611, -122.36449999999999>, <61.172999999999995, -122.36449999999999>, <60.0075, -121.199>, <60.0075, -119.761>//circle
				<60.0075, -119.761>, <60.0075, -118.323>, <61.172999999999995, -117.1575>, <62.611, -117.1575>//circle
				<49.911, -129.85750000000002>, <51.349000000000004, -129.85750000000002>, <52.5145, -131.02300000000002>, <52.5145, -132.461>//circle
				<52.5145, -132.461>, <52.5145, -133.899>, <51.349000000000004, -135.0645>, <49.911, -135.0645>//circle
				<49.911, -135.0645>, <48.473, -135.0645>, <47.307500000000005, -133.899>, <47.307500000000005, -132.461>//circle
				<47.307500000000005, -132.461>, <47.307500000000005, -131.02300000000002>, <48.473, -129.85750000000002>, <49.911, -129.85750000000002>//circle
				<62.611, -129.85750000000002>, <64.04899999999999, -129.85750000000002>, <65.21449999999999, -131.02300000000002>, <65.21449999999999, -132.461>//circle
				<65.21449999999999, -132.461>, <65.21449999999999, -133.899>, <64.04899999999999, -135.0645>, <62.611, -135.0645>//circle
				<62.611, -135.0645>, <61.172999999999995, -135.0645>, <60.0075, -133.899>, <60.0075, -132.461>//circle
				<60.0075, -132.461>, <60.0075, -131.02300000000002>, <61.172999999999995, -129.85750000000002>, <62.611, -129.85750000000002>//circle
				<49.911, -104.45750000000001>, <51.349000000000004, -104.45750000000001>, <52.5145, -105.623>, <52.5145, -107.061>//circle
				<52.5145, -107.061>, <52.5145, -108.49900000000001>, <51.349000000000004, -109.6645>, <49.911, -109.6645>//circle
				<49.911, -109.6645>, <48.473, -109.6645>, <47.307500000000005, -108.49900000000001>, <47.307500000000005, -107.061>//circle
				<47.307500000000005, -107.061>, <47.307500000000005, -105.623>, <48.473, -104.45750000000001>, <49.911, -104.45750000000001>//circle
				<62.611, -104.45750000000001>, <64.04899999999999, -104.45750000000001>, <65.21449999999999, -105.623>, <65.21449999999999, -107.061>//circle
				<65.21449999999999, -107.061>, <65.21449999999999, -108.49900000000001>, <64.04899999999999, -109.6645>, <62.611, -109.6645>//circle
				<62.611, -109.6645>, <61.172999999999995, -109.6645>, <60.0075, -108.49900000000001>, <60.0075, -107.061>//circle
				<60.0075, -107.061>, <60.0075, -105.623>, <61.172999999999995, -104.45750000000001>, <62.611, -104.45750000000001>//circle
				<84.201, -117.1575>, <85.639, -117.1575>, <86.80449999999999, -118.323>, <86.80449999999999, -119.761>//circle
				<86.80449999999999, -119.761>, <86.80449999999999, -121.199>, <85.639, -122.36449999999999>, <84.201, -122.36449999999999>//circle
				<84.201, -122.36449999999999>, <82.76299999999999, -122.36449999999999>, <81.5975, -121.199>, <81.5975, -119.761>//circle
				<81.5975, -119.761>, <81.5975, -118.323>, <82.76299999999999, -117.1575>, <84.201, -117.1575>//circle
				<96.901, -117.1575>, <98.339, -117.1575>, <99.5045, -118.323>, <99.5045, -119.761>//circle
				<99.5045, -119.761>, <99.5045, -121.199>, <98.339, -122.36449999999999>, <96.901, -122.36449999999999>//circle
				<96.901, -122.36449999999999>, <95.463, -122.36449999999999>, <94.2975, -121.199>, <94.2975, -119.761>//circle
				<94.2975, -119.761>, <94.2975, -118.323>, <95.463, -117.1575>, <96.901, -117.1575>//circle
				<84.201, -129.85750000000002>, <85.639, -129.85750000000002>, <86.80449999999999, -131.02300000000002>, <86.80449999999999, -132.461>//circle
				<86.80449999999999, -132.461>, <86.80449999999999, -133.899>, <85.639, -135.0645>, <84.201, -135.0645>//circle
				<84.201, -135.0645>, <82.76299999999999, -135.0645>, <81.5975, -133.899>, <81.5975, -132.461>//circle
				<81.5975, -132.461>, <81.5975, -131.02300000000002>, <82.76299999999999, -129.85750000000002>, <84.201, -129.85750000000002>//circle
				<96.901, -129.85750000000002>, <98.339, -129.85750000000002>, <99.5045, -131.02300000000002>, <99.5045, -132.461>//circle
				<99.5045, -132.461>, <99.5045, -133.899>, <98.339, -135.0645>, <96.901, -135.0645>//circle
				<96.901, -135.0645>, <95.463, -135.0645>, <94.2975, -133.899>, <94.2975, -132.461>//circle
				<94.2975, -132.461>, <94.2975, -131.02300000000002>, <95.463, -129.85750000000002>, <96.901, -129.85750000000002>//circle
				<84.201, -104.45750000000001>, <85.639, -104.45750000000001>, <86.80449999999999, -105.623>, <86.80449999999999, -107.061>//circle
				<86.80449999999999, -107.061>, <86.80449999999999, -108.49900000000001>, <85.639, -109.6645>, <84.201, -109.6645>//circle
				<84.201, -109.6645>, <82.76299999999999, -109.6645>, <81.5975, -108.49900000000001>, <81.5975, -107.061>//circle
				<81.5975, -107.061>, <81.5975, -105.623>, <82.76299999999999, -104.45750000000001>, <84.201, -104.45750000000001>//circle
				<96.901, -104.45750000000001>, <98.339, -104.45750000000001>, <99.5045, -105.623>, <99.5045, -107.061>//circle
				<99.5045, -107.061>, <99.5045, -108.49900000000001>, <98.339, -109.6645>, <96.901, -109.6645>//circle
				<96.901, -109.6645>, <95.463, -109.6645>, <94.2975, -108.49900000000001>, <94.2975, -107.061>//circle
				<94.2975, -107.061>, <94.2975, -105.623>, <95.463, -104.45750000000001>, <96.901, -104.45750000000001>//circle
				<129.921, -117.1575>, <131.35899999999998, -117.1575>, <132.5245, -118.323>, <132.5245, -119.761>//circle
				<132.5245, -119.761>, <132.5245, -121.199>, <131.35899999999998, -122.36449999999999>, <129.921, -122.36449999999999>//circle
				<129.921, -122.36449999999999>, <128.483, -122.36449999999999>, <127.3175, -121.199>, <127.3175, -119.761>//circle
				<127.3175, -119.761>, <127.3175, -118.323>, <128.483, -117.1575>, <129.921, -117.1575>//circle
				<142.621, -117.1575>, <144.059, -117.1575>, <145.2245, -118.323>, <145.2245, -119.761>//circle
				<145.2245, -119.761>, <145.2245, -121.199>, <144.059, -122.36449999999999>, <142.621, -122.36449999999999>//circle
				<142.621, -122.36449999999999>, <141.18300000000002, -122.36449999999999>, <140.0175, -121.199>, <140.0175, -119.761>//circle
				<140.0175, -119.761>, <140.0175, -118.323>, <141.18300000000002, -117.1575>, <142.621, -117.1575>//circle
				<129.921, -129.85750000000002>, <131.35899999999998, -129.85750000000002>, <132.5245, -131.02300000000002>, <132.5245, -132.461>//circle
				<132.5245, -132.461>, <132.5245, -133.899>, <131.35899999999998, -135.0645>, <129.921, -135.0645>//circle
				<129.921, -135.0645>, <128.483, -135.0645>, <127.3175, -133.899>, <127.3175, -132.461>//circle
				<127.3175, -132.461>, <127.3175, -131.02300000000002>, <128.483, -129.85750000000002>, <129.921, -129.85750000000002>//circle
				<142.621, -129.85750000000002>, <144.059, -129.85750000000002>, <145.2245, -131.02300000000002>, <145.2245, -132.461>//circle
				<145.2245, -132.461>, <145.2245, -133.899>, <144.059, -135.0645>, <142.621, -135.0645>//circle
				<142.621, -135.0645>, <141.18300000000002, -135.0645>, <140.0175, -133.899>, <140.0175, -132.461>//circle
				<140.0175, -132.461>, <140.0175, -131.02300000000002>, <141.18300000000002, -129.85750000000002>, <142.621, -129.85750000000002>//circle
				<129.921, -104.45750000000001>, <131.35899999999998, -104.45750000000001>, <132.5245, -105.623>, <132.5245, -107.061>//circle
				<132.5245, -107.061>, <132.5245, -108.49900000000001>, <131.35899999999998, -109.6645>, <129.921, -109.6645>//circle
				<129.921, -109.6645>, <128.483, -109.6645>, <127.3175, -108.49900000000001>, <127.3175, -107.061>//circle
				<127.3175, -107.061>, <127.3175, -105.623>, <128.483, -104.45750000000001>, <129.921, -104.45750000000001>//circle
				<142.621, -104.45750000000001>, <144.059, -104.45750000000001>, <145.2245, -105.623>, <145.2245, -107.061>//circle
				<145.2245, -107.061>, <145.2245, -108.49900000000001>, <144.059, -109.6645>, <142.621, -109.6645>//circle
				<142.621, -109.6645>, <141.18300000000002, -109.6645>, <140.0175, -108.49900000000001>, <140.0175, -107.061>//circle
				<140.0175, -107.061>, <140.0175, -105.623>, <141.18300000000002, -104.45750000000001>, <142.621, -104.45750000000001>//circle
				<164.211, -117.1575>, <165.649, -117.1575>, <166.8145, -118.323>, <166.8145, -119.761>//circle
				<166.8145, -119.761>, <166.8145, -121.199>, <165.649, -122.36449999999999>, <164.211, -122.36449999999999>//circle
				<164.211, -122.36449999999999>, <162.77300000000002, -122.36449999999999>, <161.60750000000002, -121.199>, <161.60750000000002, -119.761>//circle
				<161.60750000000002, -119.761>, <161.60750000000002, -118.323>, <162.77300000000002, -117.1575>, <164.211, -117.1575>//circle
				<176.911, -117.1575>, <178.349, -117.1575>, <179.5145, -118.323>, <179.5145, -119.761>//circle
				<179.5145, -119.761>, <179.5145, -121.199>, <178.349, -122.36449999999999>, <176.911, -122.36449999999999>//circle
				<176.911, -122.36449999999999>, <175.473, -122.36449999999999>, <174.3075, -121.199>, <174.3075, -119.761>//circle
				<174.3075, -119.761>, <174.3075, -118.323>, <175.473, -117.1575>, <176.911, -117.1575>//circle
				<164.211, -129.85750000000002>, <165.649, -129.85750000000002>, <166.8145, -131.02300000000002>, <166.8145, -132.461>//circle
				<166.8145, -132.461>, <166.8145, -133.899>, <165.649, -135.0645>, <164.211, -135.0645>//circle
				<164.211, -135.0645>, <162.77300000000002, -135.0645>, <161.60750000000002, -133.899>, <161.60750000000002, -132.461>//circle
				<161.60750000000002, -132.461>, <161.60750000000002, -131.02300000000002>, <162.77300000000002, -129.85750000000002>, <164.211, -129.85750000000002>//circle
				<176.911, -129.85750000000002>, <178.349, -129.85750000000002>, <179.5145, -131.02300000000002>, <179.5145, -132.461>//circle
				<179.5145, -132.461>, <179.5145, -133.899>, <178.349, -135.0645>, <176.911, -135.0645>//circle
				<176.911, -135.0645>, <175.473, -135.0645>, <174.3075, -133.899>, <174.3075, -132.461>//circle
				<174.3075, -132.461>, <174.3075, -131.02300000000002>, <175.473, -129.85750000000002>, <176.911, -129.85750000000002>//circle
				<164.211, -104.45750000000001>, <165.649, -104.45750000000001>, <166.8145, -105.623>, <166.8145, -107.061>//circle
				<166.8145, -107.061>, <166.8145, -108.49900000000001>, <165.649, -109.6645>, <164.211, -109.6645>//circle
				<164.211, -109.6645>, <162.77300000000002, -109.6645>, <161.60750000000002, -108.49900000000001>, <161.60750000000002, -107.061>//circle
				<161.60750000000002, -107.061>, <161.60750000000002, -105.623>, <162.77300000000002, -104.45750000000001>, <164.211, -104.45750000000001>//circle
				<176.911, -104.45750000000001>, <178.349, -104.45750000000001>, <179.5145, -105.623>, <179.5145, -107.061>//circle
				<179.5145, -107.061>, <179.5145, -108.49900000000001>, <178.349, -109.6645>, <176.911, -109.6645>//circle
				<176.911, -109.6645>, <175.473, -109.6645>, <174.3075, -108.49900000000001>, <174.3075, -107.061>//circle
				<174.3075, -107.061>, <174.3075, -105.623>, <175.473, -104.45750000000001>, <176.911, -104.45750000000001>//circle
				<49.911, -123.50750000000001>, <51.349000000000004, -123.50750000000001>, <52.5145, -124.673>, <52.5145, -126.111>//circle
				<52.5145, -126.111>, <52.5145, -127.549>, <51.349000000000004, -128.7145>, <49.911, -128.7145>//circle
				<49.911, -128.7145>, <48.473, -128.7145>, <47.307500000000005, -127.549>, <47.307500000000005, -126.111>//circle
				<47.307500000000005, -126.111>, <47.307500000000005, -124.673>, <48.473, -123.50750000000001>, <49.911, -123.50750000000001>//circle
				<62.611, -123.50750000000001>, <64.04899999999999, -123.50750000000001>, <65.21449999999999, -124.673>, <65.21449999999999, -126.111>//circle
				<65.21449999999999, -126.111>, <65.21449999999999, -127.549>, <64.04899999999999, -128.7145>, <62.611, -128.7145>//circle
				<62.611, -128.7145>, <61.172999999999995, -128.7145>, <60.0075, -127.549>, <60.0075, -126.111>//circle
				<60.0075, -126.111>, <60.0075, -124.673>, <61.172999999999995, -123.50750000000001>, <62.611, -123.50750000000001>//circle
				<49.911, -136.2075>, <51.349000000000004, -136.2075>, <52.5145, -137.37300000000002>, <52.5145, -138.811>//circle
				<52.5145, -138.811>, <52.5145, -140.249>, <51.349000000000004, -141.4145>, <49.911, -141.4145>//circle
				<49.911, -141.4145>, <48.473, -141.4145>, <47.307500000000005, -140.249>, <47.307500000000005, -138.811>//circle
				<47.307500000000005, -138.811>, <47.307500000000005, -137.37300000000002>, <48.473, -136.2075>, <49.911, -136.2075>//circle
				<62.611, -136.2075>, <64.04899999999999, -136.2075>, <65.2145, -137.37300000000002>, <65.2145, -138.811>//circle
				<65.2145, -138.811>, <65.2145, -140.249>, <64.04899999999999, -141.4145>, <62.611, -141.4145>//circle
				<62.611, -141.4145>, <61.172999999999995, -141.4145>, <60.00749999999999, -140.249>, <60.00749999999999, -138.811>//circle
				<60.00749999999999, -138.811>, <60.00749999999999, -137.37300000000002>, <61.172999999999995, -136.2075>, <62.611, -136.2075>//circle
				<49.911, -98.1075>, <51.349000000000004, -98.1075>, <52.5145, -99.273>, <52.5145, -100.711>//circle
				<52.5145, -100.711>, <52.5145, -102.149>, <51.349000000000004, -103.3145>, <49.911, -103.3145>//circle
				<49.911, -103.3145>, <48.473, -103.3145>, <47.307500000000005, -102.149>, <47.307500000000005, -100.711>//circle
				<47.307500000000005, -100.711>, <47.307500000000005, -99.273>, <48.473, -98.1075>, <49.911, -98.1075>//circle
				<62.611, -98.1075>, <64.04899999999999, -98.1075>, <65.21449999999999, -99.273>, <65.21449999999999, -100.711>//circle
				<65.21449999999999, -100.711>, <65.21449999999999, -102.149>, <64.04899999999999, -103.3145>, <62.611, -103.3145>//circle
				<62.611, -103.3145>, <61.172999999999995, -103.3145>, <60.0075, -102.149>, <60.0075, -100.711>//circle
				<60.0075, -100.711>, <60.0075, -99.273>, <61.172999999999995, -98.1075>, <62.611, -98.1075>//circle
				<49.911, -110.8075>, <51.349000000000004, -110.8075>, <52.5145, -111.973>, <52.5145, -113.411>//circle
				<52.5145, -113.411>, <52.5145, -114.849>, <51.349000000000004, -116.0145>, <49.911, -116.0145>//circle
				<49.911, -116.0145>, <48.473, -116.0145>, <47.307500000000005, -114.849>, <47.307500000000005, -113.411>//circle
				<47.307500000000005, -113.411>, <47.307500000000005, -111.973>, <48.473, -110.8075>, <49.911, -110.8075>//circle
				<62.611, -110.8075>, <64.04899999999999, -110.8075>, <65.21449999999999, -111.973>, <65.21449999999999, -113.411>//circle
				<65.21449999999999, -113.411>, <65.21449999999999, -114.849>, <64.04899999999999, -116.0145>, <62.611, -116.0145>//circle
				<62.611, -116.0145>, <61.172999999999995, -116.0145>, <60.0075, -114.849>, <60.0075, -113.411>//circle
				<60.0075, -113.411>, <60.0075, -111.973>, <61.172999999999995, -110.8075>, <62.611, -110.8075>//circle
				<84.201, -123.50750000000001>, <85.639, -123.50750000000001>, <86.80449999999999, -124.673>, <86.80449999999999, -126.111>//circle
				<86.80449999999999, -126.111>, <86.80449999999999, -127.549>, <85.639, -128.7145>, <84.201, -128.7145>//circle
				<84.201, -128.7145>, <82.76299999999999, -128.7145>, <81.5975, -127.549>, <81.5975, -126.111>//circle
				<81.5975, -126.111>, <81.5975, -124.673>, <82.76299999999999, -123.50750000000001>, <84.201, -123.50750000000001>//circle
				<96.901, -123.50750000000001>, <98.339, -123.50750000000001>, <99.5045, -124.673>, <99.5045, -126.111>//circle
				<99.5045, -126.111>, <99.5045, -127.549>, <98.339, -128.7145>, <96.901, -128.7145>//circle
				<96.901, -128.7145>, <95.463, -128.7145>, <94.2975, -127.549>, <94.2975, -126.111>//circle
				<94.2975, -126.111>, <94.2975, -124.673>, <95.463, -123.50750000000001>, <96.901, -123.50750000000001>//circle
				<84.201, -136.2075>, <85.639, -136.2075>, <86.80449999999999, -137.37300000000002>, <86.80449999999999, -138.811>//circle
				<86.80449999999999, -138.811>, <86.80449999999999, -140.249>, <85.639, -141.4145>, <84.201, -141.4145>//circle
				<84.201, -141.4145>, <82.76299999999999, -141.4145>, <81.5975, -140.249>, <81.5975, -138.811>//circle
				<81.5975, -138.811>, <81.5975, -137.37300000000002>, <82.76299999999999, -136.2075>, <84.201, -136.2075>//circle
				<96.901, -136.2075>, <98.339, -136.2075>, <99.5045, -137.37300000000002>, <99.5045, -138.811>//circle
				<99.5045, -138.811>, <99.5045, -140.249>, <98.339, -141.4145>, <96.901, -141.4145>//circle
				<96.901, -141.4145>, <95.463, -141.4145>, <94.2975, -140.249>, <94.2975, -138.811>//circle
				<94.2975, -138.811>, <94.2975, -137.37300000000002>, <95.463, -136.2075>, <96.901, -136.2075>//circle
				<84.201, -98.1075>, <85.639, -98.1075>, <86.80449999999999, -99.273>, <86.80449999999999, -100.711>//circle
				<86.80449999999999, -100.711>, <86.80449999999999, -102.149>, <85.639, -103.3145>, <84.201, -103.3145>//circle
				<84.201, -103.3145>, <82.76299999999999, -103.3145>, <81.5975, -102.149>, <81.5975, -100.711>//circle
				<81.5975, -100.711>, <81.5975, -99.273>, <82.76299999999999, -98.1075>, <84.201, -98.1075>//circle
				<96.901, -98.1075>, <98.339, -98.1075>, <99.5045, -99.273>, <99.5045, -100.711>//circle
				<99.5045, -100.711>, <99.5045, -102.149>, <98.339, -103.3145>, <96.901, -103.3145>//circle
				<96.901, -103.3145>, <95.463, -103.3145>, <94.2975, -102.149>, <94.2975, -100.711>//circle
				<94.2975, -100.711>, <94.2975, -99.273>, <95.463, -98.1075>, <96.901, -98.1075>//circle
				<84.201, -110.8075>, <85.639, -110.8075>, <86.80449999999999, -111.973>, <86.80449999999999, -113.411>//circle
				<86.80449999999999, -113.411>, <86.80449999999999, -114.849>, <85.639, -116.0145>, <84.201, -116.0145>//circle
				<84.201, -116.0145>, <82.76299999999999, -116.0145>, <81.5975, -114.849>, <81.5975, -113.411>//circle
				<81.5975, -113.411>, <81.5975, -111.973>, <82.76299999999999, -110.8075>, <84.201, -110.8075>//circle
				<96.901, -110.8075>, <98.339, -110.8075>, <99.5045, -111.973>, <99.5045, -113.411>//circle
				<99.5045, -113.411>, <99.5045, -114.849>, <98.339, -116.0145>, <96.901, -116.0145>//circle
				<96.901, -116.0145>, <95.463, -116.0145>, <94.2975, -114.849>, <94.2975, -113.411>//circle
				<94.2975, -113.411>, <94.2975, -111.973>, <95.463, -110.8075>, <96.901, -110.8075>//circle
				<129.921, -123.50750000000001>, <131.35899999999998, -123.50750000000001>, <132.5245, -124.673>, <132.5245, -126.111>//circle
				<132.5245, -126.111>, <132.5245, -127.549>, <131.35899999999998, -128.7145>, <129.921, -128.7145>//circle
				<129.921, -128.7145>, <128.483, -128.7145>, <127.3175, -127.549>, <127.3175, -126.111>//circle
				<127.3175, -126.111>, <127.3175, -124.673>, <128.483, -123.50750000000001>, <129.921, -123.50750000000001>//circle
				<142.621, -123.50750000000001>, <144.059, -123.50750000000001>, <145.2245, -124.673>, <145.2245, -126.111>//circle
				<145.2245, -126.111>, <145.2245, -127.549>, <144.059, -128.7145>, <142.621, -128.7145>//circle
				<142.621, -128.7145>, <141.18300000000002, -128.7145>, <140.0175, -127.549>, <140.0175, -126.111>//circle
				<140.0175, -126.111>, <140.0175, -124.673>, <141.18300000000002, -123.50750000000001>, <142.621, -123.50750000000001>//circle
				<129.921, -136.2075>, <131.35899999999998, -136.2075>, <132.5245, -137.37300000000002>, <132.5245, -138.811>//circle
				<132.5245, -138.811>, <132.5245, -140.249>, <131.35899999999998, -141.4145>, <129.921, -141.4145>//circle
				<129.921, -141.4145>, <128.483, -141.4145>, <127.3175, -140.249>, <127.3175, -138.811>//circle
				<127.3175, -138.811>, <127.3175, -137.37300000000002>, <128.483, -136.2075>, <129.921, -136.2075>//circle
				<142.621, -136.2075>, <144.059, -136.2075>, <145.2245, -137.37300000000002>, <145.2245, -138.811>//circle
				<145.2245, -138.811>, <145.2245, -140.249>, <144.059, -141.4145>, <142.621, -141.4145>//circle
				<142.621, -141.4145>, <141.18300000000002, -141.4145>, <140.0175, -140.249>, <140.0175, -138.811>//circle
				<140.0175, -138.811>, <140.0175, -137.37300000000002>, <141.18300000000002, -136.2075>, <142.621, -136.2075>//circle
				<129.921, -98.1075>, <131.35899999999998, -98.1075>, <132.5245, -99.273>, <132.5245, -100.711>//circle
				<132.5245, -100.711>, <132.5245, -102.149>, <131.35899999999998, -103.3145>, <129.921, -103.3145>//circle
				<129.921, -103.3145>, <128.483, -103.3145>, <127.3175, -102.149>, <127.3175, -100.711>//circle
				<127.3175, -100.711>, <127.3175, -99.273>, <128.483, -98.1075>, <129.921, -98.1075>//circle
				<142.621, -98.1075>, <144.059, -98.1075>, <145.2245, -99.273>, <145.2245, -100.711>//circle
				<145.2245, -100.711>, <145.2245, -102.149>, <144.059, -103.3145>, <142.621, -103.3145>//circle
				<142.621, -103.3145>, <141.18300000000002, -103.3145>, <140.0175, -102.149>, <140.0175, -100.711>//circle
				<140.0175, -100.711>, <140.0175, -99.273>, <141.18300000000002, -98.1075>, <142.621, -98.1075>//circle
				<129.921, -110.8075>, <131.35899999999998, -110.8075>, <132.5245, -111.973>, <132.5245, -113.411>//circle
				<132.5245, -113.411>, <132.5245, -114.849>, <131.35899999999998, -116.0145>, <129.921, -116.0145>//circle
				<129.921, -116.0145>, <128.483, -116.0145>, <127.3175, -114.849>, <127.3175, -113.411>//circle
				<127.3175, -113.411>, <127.3175, -111.973>, <128.483, -110.8075>, <129.921, -110.8075>//circle
				<142.621, -110.8075>, <144.059, -110.8075>, <145.2245, -111.973>, <145.2245, -113.411>//circle
				<145.2245, -113.411>, <145.2245, -114.849>, <144.059, -116.0145>, <142.621, -116.0145>//circle
				<142.621, -116.0145>, <141.18300000000002, -116.0145>, <140.0175, -114.849>, <140.0175, -113.411>//circle
				<140.0175, -113.411>, <140.0175, -111.973>, <141.18300000000002, -110.8075>, <142.621, -110.8075>//circle
				<164.211, -123.50750000000001>, <165.649, -123.50750000000001>, <166.8145, -124.673>, <166.8145, -126.111>//circle
				<166.8145, -126.111>, <166.8145, -127.549>, <165.649, -128.7145>, <164.211, -128.7145>//circle
				<164.211, -128.7145>, <162.77300000000002, -128.7145>, <161.60750000000002, -127.549>, <161.60750000000002, -126.111>//circle
				<161.60750000000002, -126.111>, <161.60750000000002, -124.673>, <162.77300000000002, -123.50750000000001>, <164.211, -123.50750000000001>//circle
				<176.911, -123.50750000000001>, <178.349, -123.50750000000001>, <179.5145, -124.673>, <179.5145, -126.111>//circle
				<179.5145, -126.111>, <179.5145, -127.549>, <178.349, -128.7145>, <176.911, -128.7145>//circle
				<176.911, -128.7145>, <175.473, -128.7145>, <174.3075, -127.549>, <174.3075, -126.111>//circle
				<174.3075, -126.111>, <174.3075, -124.673>, <175.473, -123.50750000000001>, <176.911, -123.50750000000001>//circle
				<164.211, -136.2075>, <165.649, -136.2075>, <166.8145, -137.37300000000002>, <166.8145, -138.811>//circle
				<166.8145, -138.811>, <166.8145, -140.249>, <165.649, -141.4145>, <164.211, -141.4145>//circle
				<164.211, -141.4145>, <162.77300000000002, -141.4145>, <161.60750000000002, -140.249>, <161.60750000000002, -138.811>//circle
				<161.60750000000002, -138.811>, <161.60750000000002, -137.37300000000002>, <162.77300000000002, -136.2075>, <164.211, -136.2075>//circle
				<176.911, -136.2075>, <178.349, -136.2075>, <179.5145, -137.37300000000002>, <179.5145, -138.811>//circle
				<179.5145, -138.811>, <179.5145, -140.249>, <178.349, -141.4145>, <176.911, -141.4145>//circle
				<176.911, -141.4145>, <175.473, -141.4145>, <174.3075, -140.249>, <174.3075, -138.811>//circle
				<174.3075, -138.811>, <174.3075, -137.37300000000002>, <175.473, -136.2075>, <176.911, -136.2075>//circle
				<164.211, -98.1075>, <165.649, -98.1075>, <166.8145, -99.273>, <166.8145, -100.711>//circle
				<166.8145, -100.711>, <166.8145, -102.149>, <165.649, -103.3145>, <164.211, -103.3145>//circle
				<164.211, -103.3145>, <162.77300000000002, -103.3145>, <161.60750000000002, -102.149>, <161.60750000000002, -100.711>//circle
				<161.60750000000002, -100.711>, <161.60750000000002, -99.273>, <162.77300000000002, -98.1075>, <164.211, -98.1075>//circle
				<176.911, -98.1075>, <178.349, -98.1075>, <179.5145, -99.273>, <179.5145, -100.711>//circle
				<179.5145, -100.711>, <179.5145, -102.149>, <178.349, -103.3145>, <176.911, -103.3145>//circle
				<176.911, -103.3145>, <175.473, -103.3145>, <174.3075, -102.149>, <174.3075, -100.711>//circle
				<174.3075, -100.711>, <174.3075, -99.273>, <175.473, -98.1075>, <176.911, -98.1075>//circle
				<164.211, -110.8075>, <165.649, -110.8075>, <166.8145, -111.973>, <166.8145, -113.411>//circle
				<166.8145, -113.411>, <166.8145, -114.849>, <165.649, -116.0145>, <164.211, -116.0145>//circle
				<164.211, -116.0145>, <162.77300000000002, -116.0145>, <161.60750000000002, -114.849>, <161.60750000000002, -113.411>//circle
				<161.60750000000002, -113.411>, <161.60750000000002, -111.973>, <162.77300000000002, -110.8075>, <164.211, -110.8075>//circle
				<176.911, -110.8075>, <178.349, -110.8075>, <179.5145, -111.973>, <179.5145, -113.411>//circle
				<179.5145, -113.411>, <179.5145, -114.849>, <178.349, -116.0145>, <176.911, -116.0145>//circle
				<176.911, -116.0145>, <175.473, -116.0145>, <174.3075, -114.849>, <174.3075, -113.411>//circle
				<174.3075, -113.411>, <174.3075, -111.973>, <175.473, -110.8075>, <176.911, -110.8075>//circle
				<56.261, -117.1575>, <57.699000000000005, -117.1575>, <58.8645, -118.323>, <58.8645, -119.761>//circle
				<58.8645, -119.761>, <58.8645, -121.199>, <57.699000000000005, -122.36449999999999>, <56.261, -122.36449999999999>//circle
				<56.261, -122.36449999999999>, <54.823, -122.36449999999999>, <53.657500000000006, -121.199>, <53.657500000000006, -119.761>//circle
				<53.657500000000006, -119.761>, <53.657500000000006, -118.323>, <54.823, -117.1575>, <56.261, -117.1575>//circle
				<68.961, -117.1575>, <70.399, -117.1575>, <71.5645, -118.323>, <71.5645, -119.761>//circle
				<71.5645, -119.761>, <71.5645, -121.199>, <70.399, -122.36449999999999>, <68.961, -122.36449999999999>//circle
				<68.961, -122.36449999999999>, <67.523, -122.36449999999999>, <66.3575, -121.199>, <66.3575, -119.761>//circle
				<66.3575, -119.761>, <66.3575, -118.323>, <67.523, -117.1575>, <68.961, -117.1575>//circle
				<75.311, -117.1575>, <76.74900000000001, -117.1575>, <77.9145, -118.323>, <77.9145, -119.761>//circle
				<77.9145, -119.761>, <77.9145, -121.199>, <76.74900000000001, -122.36449999999999>, <75.311, -122.36449999999999>//circle
				<75.311, -122.36449999999999>, <73.873, -122.36449999999999>, <72.70750000000001, -121.199>, <72.70750000000001, -119.761>//circle
				<72.70750000000001, -119.761>, <72.70750000000001, -118.323>, <73.873, -117.1575>, <75.311, -117.1575>//circle
				<56.261, -129.85750000000002>, <57.699000000000005, -129.85750000000002>, <58.8645, -131.02300000000002>, <58.8645, -132.461>//circle
				<58.8645, -132.461>, <58.8645, -133.899>, <57.699000000000005, -135.0645>, <56.261, -135.0645>//circle
				<56.261, -135.0645>, <54.823, -135.0645>, <53.657500000000006, -133.899>, <53.657500000000006, -132.461>//circle
				<53.657500000000006, -132.461>, <53.657500000000006, -131.02300000000002>, <54.823, -129.85750000000002>, <56.261, -129.85750000000002>//circle
				<68.961, -129.85750000000002>, <70.399, -129.85750000000002>, <71.5645, -131.02300000000002>, <71.5645, -132.461>//circle
				<71.5645, -132.461>, <71.5645, -133.899>, <70.399, -135.0645>, <68.961, -135.0645>//circle
				<68.961, -135.0645>, <67.523, -135.0645>, <66.3575, -133.899>, <66.3575, -132.461>//circle
				<66.3575, -132.461>, <66.3575, -131.02300000000002>, <67.523, -129.85750000000002>, <68.961, -129.85750000000002>//circle
				<75.311, -129.85750000000002>, <76.74900000000001, -129.85750000000002>, <77.9145, -131.02300000000002>, <77.9145, -132.461>//circle
				<77.9145, -132.461>, <77.9145, -133.899>, <76.74900000000001, -135.0645>, <75.311, -135.0645>//circle
				<75.311, -135.0645>, <73.873, -135.0645>, <72.70750000000001, -133.899>, <72.70750000000001, -132.461>//circle
				<72.70750000000001, -132.461>, <72.70750000000001, -131.02300000000002>, <73.873, -129.85750000000002>, <75.311, -129.85750000000002>//circle
				<56.261, -104.45750000000001>, <57.699000000000005, -104.45750000000001>, <58.8645, -105.623>, <58.8645, -107.061>//circle
				<58.8645, -107.061>, <58.8645, -108.49900000000001>, <57.699000000000005, -109.6645>, <56.261, -109.6645>//circle
				<56.261, -109.6645>, <54.823, -109.6645>, <53.657500000000006, -108.49900000000001>, <53.657500000000006, -107.061>//circle
				<53.657500000000006, -107.061>, <53.657500000000006, -105.623>, <54.823, -104.45750000000001>, <56.261, -104.45750000000001>//circle
				<68.961, -104.45750000000001>, <70.399, -104.45750000000001>, <71.5645, -105.623>, <71.5645, -107.061>//circle
				<71.5645, -107.061>, <71.5645, -108.49900000000001>, <70.399, -109.6645>, <68.961, -109.6645>//circle
				<68.961, -109.6645>, <67.523, -109.6645>, <66.3575, -108.49900000000001>, <66.3575, -107.061>//circle
				<66.3575, -107.061>, <66.3575, -105.623>, <67.523, -104.45750000000001>, <68.961, -104.45750000000001>//circle
				<75.311, -104.45750000000001>, <76.74900000000001, -104.45750000000001>, <77.9145, -105.623>, <77.9145, -107.061>//circle
				<77.9145, -107.061>, <77.9145, -108.49900000000001>, <76.74900000000001, -109.6645>, <75.311, -109.6645>//circle
				<75.311, -109.6645>, <73.873, -109.6645>, <72.70750000000001, -108.49900000000001>, <72.70750000000001, -107.061>//circle
				<72.70750000000001, -107.061>, <72.70750000000001, -105.623>, <73.873, -104.45750000000001>, <75.311, -104.45750000000001>//circle
				<90.551, -117.1575>, <91.989, -117.1575>, <93.1545, -118.323>, <93.1545, -119.761>//circle
				<93.1545, -119.761>, <93.1545, -121.199>, <91.989, -122.36449999999999>, <90.551, -122.36449999999999>//circle
				<90.551, -122.36449999999999>, <89.113, -122.36449999999999>, <87.9475, -121.199>, <87.9475, -119.761>//circle
				<87.9475, -119.761>, <87.9475, -118.323>, <89.113, -117.1575>, <90.551, -117.1575>//circle
				<103.251, -117.1575>, <104.68900000000001, -117.1575>, <105.8545, -118.323>, <105.8545, -119.761>//circle
				<105.8545, -119.761>, <105.8545, -121.199>, <104.68900000000001, -122.36449999999999>, <103.251, -122.36449999999999>//circle
				<103.251, -122.36449999999999>, <101.813, -122.36449999999999>, <100.64750000000001, -121.199>, <100.64750000000001, -119.761>//circle
				<100.64750000000001, -119.761>, <100.64750000000001, -118.323>, <101.813, -117.1575>, <103.251, -117.1575>//circle
				<109.601, -117.1575>, <111.039, -117.1575>, <112.2045, -118.323>, <112.2045, -119.761>//circle
				<112.2045, -119.761>, <112.2045, -121.199>, <111.039, -122.36449999999999>, <109.601, -122.36449999999999>//circle
				<109.601, -122.36449999999999>, <108.163, -122.36449999999999>, <106.9975, -121.199>, <106.9975, -119.761>//circle
				<106.9975, -119.761>, <106.9975, -118.323>, <108.163, -117.1575>, <109.601, -117.1575>//circle
				<90.551, -129.85750000000002>, <91.989, -129.85750000000002>, <93.1545, -131.02300000000002>, <93.1545, -132.461>//circle
				<93.1545, -132.461>, <93.1545, -133.899>, <91.989, -135.0645>, <90.551, -135.0645>//circle
				<90.551, -135.0645>, <89.113, -135.0645>, <87.9475, -133.899>, <87.9475, -132.461>//circle
				<87.9475, -132.461>, <87.9475, -131.02300000000002>, <89.113, -129.85750000000002>, <90.551, -129.85750000000002>//circle
				<103.251, -129.85750000000002>, <104.68900000000001, -129.85750000000002>, <105.8545, -131.02300000000002>, <105.8545, -132.461>//circle
				<105.8545, -132.461>, <105.8545, -133.899>, <104.68900000000001, -135.0645>, <103.251, -135.0645>//circle
				<103.251, -135.0645>, <101.813, -135.0645>, <100.64750000000001, -133.899>, <100.64750000000001, -132.461>//circle
				<100.64750000000001, -132.461>, <100.64750000000001, -131.02300000000002>, <101.813, -129.85750000000002>, <103.251, -129.85750000000002>//circle
				<109.601, -129.85750000000002>, <111.039, -129.85750000000002>, <112.2045, -131.02300000000002>, <112.2045, -132.461>//circle
				<112.2045, -132.461>, <112.2045, -133.899>, <111.039, -135.0645>, <109.601, -135.0645>//circle
				<109.601, -135.0645>, <108.163, -135.0645>, <106.9975, -133.899>, <106.9975, -132.461>//circle
				<106.9975, -132.461>, <106.9975, -131.02300000000002>, <108.163, -129.85750000000002>, <109.601, -129.85750000000002>//circle
				<90.551, -104.45750000000001>, <91.989, -104.45750000000001>, <93.1545, -105.623>, <93.1545, -107.061>//circle
				<93.1545, -107.061>, <93.1545, -108.49900000000001>, <91.989, -109.6645>, <90.551, -109.6645>//circle
				<90.551, -109.6645>, <89.113, -109.6645>, <87.9475, -108.49900000000001>, <87.9475, -107.061>//circle
				<87.9475, -107.061>, <87.9475, -105.623>, <89.113, -104.45750000000001>, <90.551, -104.45750000000001>//circle
				<103.251, -104.45750000000001>, <104.68900000000001, -104.45750000000001>, <105.8545, -105.623>, <105.8545, -107.061>//circle
				<105.8545, -107.061>, <105.8545, -108.49900000000001>, <104.68900000000001, -109.6645>, <103.251, -109.6645>//circle
				<103.251, -109.6645>, <101.813, -109.6645>, <100.64750000000001, -108.49900000000001>, <100.64750000000001, -107.061>//circle
				<100.64750000000001, -107.061>, <100.64750000000001, -105.623>, <101.813, -104.45750000000001>, <103.251, -104.45750000000001>//circle
				<109.601, -104.45750000000001>, <111.039, -104.45750000000001>, <112.2045, -105.623>, <112.2045, -107.061>//circle
				<112.2045, -107.061>, <112.2045, -108.49900000000001>, <111.039, -109.6645>, <109.601, -109.6645>//circle
				<109.601, -109.6645>, <108.163, -109.6645>, <106.9975, -108.49900000000001>, <106.9975, -107.061>//circle
				<106.9975, -107.061>, <106.9975, -105.623>, <108.163, -104.45750000000001>, <109.601, -104.45750000000001>//circle
				<136.271, -117.1575>, <137.70899999999997, -117.1575>, <138.87449999999998, -118.323>, <138.87449999999998, -119.761>//circle
				<138.87449999999998, -119.761>, <138.87449999999998, -121.199>, <137.70899999999997, -122.36449999999999>, <136.271, -122.36449999999999>//circle
				<136.271, -122.36449999999999>, <134.833, -122.36449999999999>, <133.6675, -121.199>, <133.6675, -119.761>//circle
				<133.6675, -119.761>, <133.6675, -118.323>, <134.833, -117.1575>, <136.271, -117.1575>//circle
				<148.971, -117.1575>, <150.409, -117.1575>, <151.5745, -118.323>, <151.5745, -119.761>//circle
				<151.5745, -119.761>, <151.5745, -121.199>, <150.409, -122.36449999999999>, <148.971, -122.36449999999999>//circle
				<148.971, -122.36449999999999>, <147.53300000000002, -122.36449999999999>, <146.3675, -121.199>, <146.3675, -119.761>//circle
				<146.3675, -119.761>, <146.3675, -118.323>, <147.53300000000002, -117.1575>, <148.971, -117.1575>//circle
				<155.321, -117.1575>, <156.759, -117.1575>, <157.9245, -118.323>, <157.9245, -119.761>//circle
				<157.9245, -119.761>, <157.9245, -121.199>, <156.759, -122.36449999999999>, <155.321, -122.36449999999999>//circle
				<155.321, -122.36449999999999>, <153.883, -122.36449999999999>, <152.7175, -121.199>, <152.7175, -119.761>//circle
				<152.7175, -119.761>, <152.7175, -118.323>, <153.883, -117.1575>, <155.321, -117.1575>//circle
				<136.271, -129.85750000000002>, <137.70899999999997, -129.85750000000002>, <138.87449999999998, -131.02300000000002>, <138.87449999999998, -132.461>//circle
				<138.87449999999998, -132.461>, <138.87449999999998, -133.899>, <137.70899999999997, -135.0645>, <136.271, -135.0645>//circle
				<136.271, -135.0645>, <134.833, -135.0645>, <133.6675, -133.899>, <133.6675, -132.461>//circle
				<133.6675, -132.461>, <133.6675, -131.02300000000002>, <134.833, -129.85750000000002>, <136.271, -129.85750000000002>//circle
				<148.971, -129.85750000000002>, <150.409, -129.85750000000002>, <151.5745, -131.02300000000002>, <151.5745, -132.461>//circle
				<151.5745, -132.461>, <151.5745, -133.899>, <150.409, -135.0645>, <148.971, -135.0645>//circle
				<148.971, -135.0645>, <147.53300000000002, -135.0645>, <146.3675, -133.899>, <146.3675, -132.461>//circle
				<146.3675, -132.461>, <146.3675, -131.02300000000002>, <147.53300000000002, -129.85750000000002>, <148.971, -129.85750000000002>//circle
				<155.321, -129.85750000000002>, <156.759, -129.85750000000002>, <157.9245, -131.02300000000002>, <157.9245, -132.461>//circle
				<157.9245, -132.461>, <157.9245, -133.899>, <156.759, -135.0645>, <155.321, -135.0645>//circle
				<155.321, -135.0645>, <153.883, -135.0645>, <152.7175, -133.899>, <152.7175, -132.461>//circle
				<152.7175, -132.461>, <152.7175, -131.02300000000002>, <153.883, -129.85750000000002>, <155.321, -129.85750000000002>//circle
				<136.271, -104.45750000000001>, <137.70899999999997, -104.45750000000001>, <138.87449999999998, -105.623>, <138.87449999999998, -107.061>//circle
				<138.87449999999998, -107.061>, <138.87449999999998, -108.49900000000001>, <137.70899999999997, -109.6645>, <136.271, -109.6645>//circle
				<136.271, -109.6645>, <134.833, -109.6645>, <133.6675, -108.49900000000001>, <133.6675, -107.061>//circle
				<133.6675, -107.061>, <133.6675, -105.623>, <134.833, -104.45750000000001>, <136.271, -104.45750000000001>//circle
				<148.971, -104.45750000000001>, <150.409, -104.45750000000001>, <151.5745, -105.623>, <151.5745, -107.061>//circle
				<151.5745, -107.061>, <151.5745, -108.49900000000001>, <150.409, -109.6645>, <148.971, -109.6645>//circle
				<148.971, -109.6645>, <147.53300000000002, -109.6645>, <146.3675, -108.49900000000001>, <146.3675, -107.061>//circle
				<146.3675, -107.061>, <146.3675, -105.623>, <147.53300000000002, -104.45750000000001>, <148.971, -104.45750000000001>//circle
				<155.321, -104.45750000000001>, <156.759, -104.45750000000001>, <157.9245, -105.623>, <157.9245, -107.061>//circle
				<157.9245, -107.061>, <157.9245, -108.49900000000001>, <156.759, -109.6645>, <155.321, -109.6645>//circle
				<155.321, -109.6645>, <153.883, -109.6645>, <152.7175, -108.49900000000001>, <152.7175, -107.061>//circle
				<152.7175, -107.061>, <152.7175, -105.623>, <153.883, -104.45750000000001>, <155.321, -104.45750000000001>//circle
				<170.561, -117.1575>, <171.999, -117.1575>, <173.1645, -118.323>, <173.1645, -119.761>//circle
				<173.1645, -119.761>, <173.1645, -121.199>, <171.999, -122.36449999999999>, <170.561, -122.36449999999999>//circle
				<170.561, -122.36449999999999>, <169.12300000000002, -122.36449999999999>, <167.9575, -121.199>, <167.9575, -119.761>//circle
				<167.9575, -119.761>, <167.9575, -118.323>, <169.12300000000002, -117.1575>, <170.561, -117.1575>//circle
				<183.261, -117.1575>, <184.69899999999998, -117.1575>, <185.8645, -118.323>, <185.8645, -119.761>//circle
				<185.8645, -119.761>, <185.8645, -121.199>, <184.69899999999998, -122.36449999999999>, <183.261, -122.36449999999999>//circle
				<183.261, -122.36449999999999>, <181.823, -122.36449999999999>, <180.6575, -121.199>, <180.6575, -119.761>//circle
				<180.6575, -119.761>, <180.6575, -118.323>, <181.823, -117.1575>, <183.261, -117.1575>//circle
				<189.611, -117.1575>, <191.04899999999998, -117.1575>, <192.2145, -118.323>, <192.2145, -119.761>//circle
				<192.2145, -119.761>, <192.2145, -121.199>, <191.04899999999998, -122.36449999999999>, <189.611, -122.36449999999999>//circle
				<189.611, -122.36449999999999>, <188.173, -122.36449999999999>, <187.0075, -121.199>, <187.0075, -119.761>//circle
				<187.0075, -119.761>, <187.0075, -118.323>, <188.173, -117.1575>, <189.611, -117.1575>//circle
				<170.561, -129.85750000000002>, <171.999, -129.85750000000002>, <173.1645, -131.02300000000002>, <173.1645, -132.461>//circle
				<173.1645, -132.461>, <173.1645, -133.899>, <171.999, -135.0645>, <170.561, -135.0645>//circle
				<170.561, -135.0645>, <169.12300000000002, -135.0645>, <167.9575, -133.899>, <167.9575, -132.461>//circle
				<167.9575, -132.461>, <167.9575, -131.02300000000002>, <169.12300000000002, -129.85750000000002>, <170.561, -129.85750000000002>//circle
				<183.261, -129.85750000000002>, <184.69899999999998, -129.85750000000002>, <185.8645, -131.02300000000002>, <185.8645, -132.461>//circle
				<185.8645, -132.461>, <185.8645, -133.899>, <184.69899999999998, -135.0645>, <183.261, -135.0645>//circle
				<183.261, -135.0645>, <181.823, -135.0645>, <180.6575, -133.899>, <180.6575, -132.461>//circle
				<180.6575, -132.461>, <180.6575, -131.02300000000002>, <181.823, -129.85750000000002>, <183.261, -129.85750000000002>//circle
				<189.611, -129.85750000000002>, <191.04899999999998, -129.85750000000002>, <192.2145, -131.02300000000002>, <192.2145, -132.461>//circle
				<192.2145, -132.461>, <192.2145, -133.899>, <191.04899999999998, -135.0645>, <189.611, -135.0645>//circle
				<189.611, -135.0645>, <188.173, -135.0645>, <187.0075, -133.899>, <187.0075, -132.461>//circle
				<187.0075, -132.461>, <187.0075, -131.02300000000002>, <188.173, -129.85750000000002>, <189.611, -129.85750000000002>//circle
				<170.561, -104.45750000000001>, <171.999, -104.45750000000001>, <173.1645, -105.623>, <173.1645, -107.061>//circle
				<173.1645, -107.061>, <173.1645, -108.49900000000001>, <171.999, -109.6645>, <170.561, -109.6645>//circle
				<170.561, -109.6645>, <169.12300000000002, -109.6645>, <167.9575, -108.49900000000001>, <167.9575, -107.061>//circle
				<167.9575, -107.061>, <167.9575, -105.623>, <169.12300000000002, -104.45750000000001>, <170.561, -104.45750000000001>//circle
				<183.261, -104.45750000000001>, <184.69899999999998, -104.45750000000001>, <185.8645, -105.623>, <185.8645, -107.061>//circle
				<185.8645, -107.061>, <185.8645, -108.49900000000001>, <184.69899999999998, -109.6645>, <183.261, -109.6645>//circle
				<183.261, -109.6645>, <181.823, -109.6645>, <180.6575, -108.49900000000001>, <180.6575, -107.061>//circle
				<180.6575, -107.061>, <180.6575, -105.623>, <181.823, -104.45750000000001>, <183.261, -104.45750000000001>//circle
				<189.611, -104.45750000000001>, <191.04899999999998, -104.45750000000001>, <192.2145, -105.623>, <192.2145, -107.061>//circle
				<192.2145, -107.061>, <192.2145, -108.49900000000001>, <191.04899999999998, -109.6645>, <189.611, -109.6645>//circle
				<189.611, -109.6645>, <188.173, -109.6645>, <187.0075, -108.49900000000001>, <187.0075, -107.061>//circle
				<187.0075, -107.061>, <187.0075, -105.623>, <188.173, -104.45750000000001>, <189.611, -104.45750000000001>//circle
				<56.261, -123.50750000000001>, <57.699000000000005, -123.50750000000001>, <58.8645, -124.673>, <58.8645, -126.111>//circle
				<58.8645, -126.111>, <58.8645, -127.549>, <57.699000000000005, -128.7145>, <56.261, -128.7145>//circle
				<56.261, -128.7145>, <54.823, -128.7145>, <53.657500000000006, -127.549>, <53.657500000000006, -126.111>//circle
				<53.657500000000006, -126.111>, <53.657500000000006, -124.673>, <54.823, -123.50750000000001>, <56.261, -123.50750000000001>//circle
				<68.961, -123.50750000000001>, <70.399, -123.50750000000001>, <71.5645, -124.673>, <71.5645, -126.111>//circle
				<71.5645, -126.111>, <71.5645, -127.549>, <70.399, -128.7145>, <68.961, -128.7145>//circle
				<68.961, -128.7145>, <67.523, -128.7145>, <66.3575, -127.549>, <66.3575, -126.111>//circle
				<66.3575, -126.111>, <66.3575, -124.673>, <67.523, -123.50750000000001>, <68.961, -123.50750000000001>//circle
				<75.311, -123.50750000000001>, <76.74900000000001, -123.50750000000001>, <77.9145, -124.673>, <77.9145, -126.111>//circle
				<77.9145, -126.111>, <77.9145, -127.549>, <76.74900000000001, -128.7145>, <75.311, -128.7145>//circle
				<75.311, -128.7145>, <73.873, -128.7145>, <72.70750000000001, -127.549>, <72.70750000000001, -126.111>//circle
				<72.70750000000001, -126.111>, <72.70750000000001, -124.673>, <73.873, -123.50750000000001>, <75.311, -123.50750000000001>//circle
				<56.261, -136.2075>, <57.699000000000005, -136.2075>, <58.8645, -137.37300000000002>, <58.8645, -138.811>//circle
				<58.8645, -138.811>, <58.8645, -140.249>, <57.699000000000005, -141.4145>, <56.261, -141.4145>//circle
				<56.261, -141.4145>, <54.823, -141.4145>, <53.657500000000006, -140.249>, <53.657500000000006, -138.811>//circle
				<53.657500000000006, -138.811>, <53.657500000000006, -137.37300000000002>, <54.823, -136.2075>, <56.261, -136.2075>//circle
				<68.961, -136.2075>, <70.399, -136.2075>, <71.5645, -137.37300000000002>, <71.5645, -138.811>//circle
				<71.5645, -138.811>, <71.5645, -140.249>, <70.399, -141.4145>, <68.961, -141.4145>//circle
				<68.961, -141.4145>, <67.523, -141.4145>, <66.3575, -140.249>, <66.3575, -138.811>//circle
				<66.3575, -138.811>, <66.3575, -137.37300000000002>, <67.523, -136.2075>, <68.961, -136.2075>//circle
				<75.311, -136.2075>, <76.74900000000001, -136.2075>, <77.9145, -137.37300000000002>, <77.9145, -138.811>//circle
				<77.9145, -138.811>, <77.9145, -140.249>, <76.74900000000001, -141.4145>, <75.311, -141.4145>//circle
				<75.311, -141.4145>, <73.873, -141.4145>, <72.70750000000001, -140.249>, <72.70750000000001, -138.811>//circle
				<72.70750000000001, -138.811>, <72.70750000000001, -137.37300000000002>, <73.873, -136.2075>, <75.311, -136.2075>//circle
				<56.261, -98.1075>, <57.699000000000005, -98.1075>, <58.8645, -99.273>, <58.8645, -100.711>//circle
				<58.8645, -100.711>, <58.8645, -102.149>, <57.699000000000005, -103.3145>, <56.261, -103.3145>//circle
				<56.261, -103.3145>, <54.823, -103.3145>, <53.657500000000006, -102.149>, <53.657500000000006, -100.711>//circle
				<53.657500000000006, -100.711>, <53.657500000000006, -99.273>, <54.823, -98.1075>, <56.261, -98.1075>//circle
				<68.961, -98.1075>, <70.399, -98.1075>, <71.5645, -99.273>, <71.5645, -100.711>//circle
				<71.5645, -100.711>, <71.5645, -102.149>, <70.399, -103.3145>, <68.961, -103.3145>//circle
				<68.961, -103.3145>, <67.523, -103.3145>, <66.3575, -102.149>, <66.3575, -100.711>//circle
				<66.3575, -100.711>, <66.3575, -99.273>, <67.523, -98.1075>, <68.961, -98.1075>//circle
				<75.311, -98.1075>, <76.74900000000001, -98.1075>, <77.9145, -99.273>, <77.9145, -100.711>//circle
				<77.9145, -100.711>, <77.9145, -102.149>, <76.74900000000001, -103.3145>, <75.311, -103.3145>//circle
				<75.311, -103.3145>, <73.873, -103.3145>, <72.70750000000001, -102.149>, <72.70750000000001, -100.711>//circle
				<72.70750000000001, -100.711>, <72.70750000000001, -99.273>, <73.873, -98.1075>, <75.311, -98.1075>//circle
				<56.261, -110.8075>, <57.699000000000005, -110.8075>, <58.8645, -111.973>, <58.8645, -113.411>//circle
				<58.8645, -113.411>, <58.8645, -114.849>, <57.699000000000005, -116.0145>, <56.261, -116.0145>//circle
				<56.261, -116.0145>, <54.823, -116.0145>, <53.657500000000006, -114.849>, <53.657500000000006, -113.411>//circle
				<53.657500000000006, -113.411>, <53.657500000000006, -111.973>, <54.823, -110.8075>, <56.261, -110.8075>//circle
				<68.961, -110.8075>, <70.399, -110.8075>, <71.5645, -111.973>, <71.5645, -113.411>//circle
				<71.5645, -113.411>, <71.5645, -114.849>, <70.399, -116.0145>, <68.961, -116.0145>//circle
				<68.961, -116.0145>, <67.523, -116.0145>, <66.3575, -114.849>, <66.3575, -113.411>//circle
				<66.3575, -113.411>, <66.3575, -111.973>, <67.523, -110.8075>, <68.961, -110.8075>//circle
				<75.311, -110.8075>, <76.74900000000001, -110.8075>, <77.9145, -111.973>, <77.9145, -113.411>//circle
				<77.9145, -113.411>, <77.9145, -114.849>, <76.74900000000001, -116.0145>, <75.311, -116.0145>//circle
				<75.311, -116.0145>, <73.873, -116.0145>, <72.70750000000001, -114.849>, <72.70750000000001, -113.411>//circle
				<72.70750000000001, -113.411>, <72.70750000000001, -111.973>, <73.873, -110.8075>, <75.311, -110.8075>//circle
				<90.551, -123.50750000000001>, <91.989, -123.50750000000001>, <93.1545, -124.673>, <93.1545, -126.111>//circle
				<93.1545, -126.111>, <93.1545, -127.549>, <91.989, -128.7145>, <90.551, -128.7145>//circle
				<90.551, -128.7145>, <89.113, -128.7145>, <87.9475, -127.549>, <87.9475, -126.111>//circle
				<87.9475, -126.111>, <87.9475, -124.673>, <89.113, -123.50750000000001>, <90.551, -123.50750000000001>//circle
				<103.251, -123.50750000000001>, <104.68900000000001, -123.50750000000001>, <105.8545, -124.673>, <105.8545, -126.111>//circle
				<105.8545, -126.111>, <105.8545, -127.549>, <104.68900000000001, -128.7145>, <103.251, -128.7145>//circle
				<103.251, -128.7145>, <101.813, -128.7145>, <100.64750000000001, -127.549>, <100.64750000000001, -126.111>//circle
				<100.64750000000001, -126.111>, <100.64750000000001, -124.673>, <101.813, -123.50750000000001>, <103.251, -123.50750000000001>//circle
				<109.601, -123.50750000000001>, <111.039, -123.50750000000001>, <112.2045, -124.673>, <112.2045, -126.111>//circle
				<112.2045, -126.111>, <112.2045, -127.549>, <111.039, -128.7145>, <109.601, -128.7145>//circle
				<109.601, -128.7145>, <108.163, -128.7145>, <106.9975, -127.549>, <106.9975, -126.111>//circle
				<106.9975, -126.111>, <106.9975, -124.673>, <108.163, -123.50750000000001>, <109.601, -123.50750000000001>//circle
				<90.551, -136.2075>, <91.989, -136.2075>, <93.1545, -137.37300000000002>, <93.1545, -138.811>//circle
				<93.1545, -138.811>, <93.1545, -140.249>, <91.989, -141.4145>, <90.551, -141.4145>//circle
				<90.551, -141.4145>, <89.113, -141.4145>, <87.9475, -140.249>, <87.9475, -138.811>//circle
				<87.9475, -138.811>, <87.9475, -137.37300000000002>, <89.113, -136.2075>, <90.551, -136.2075>//circle
				<103.251, -136.2075>, <104.68900000000001, -136.2075>, <105.8545, -137.37300000000002>, <105.8545, -138.811>//circle
				<105.8545, -138.811>, <105.8545, -140.249>, <104.68900000000001, -141.4145>, <103.251, -141.4145>//circle
				<103.251, -141.4145>, <101.813, -141.4145>, <100.64750000000001, -140.249>, <100.64750000000001, -138.811>//circle
				<100.64750000000001, -138.811>, <100.64750000000001, -137.37300000000002>, <101.813, -136.2075>, <103.251, -136.2075>//circle
				<109.601, -136.2075>, <111.039, -136.2075>, <112.2045, -137.37300000000002>, <112.2045, -138.811>//circle
				<112.2045, -138.811>, <112.2045, -140.249>, <111.039, -141.4145>, <109.601, -141.4145>//circle
				<109.601, -141.4145>, <108.163, -141.4145>, <106.9975, -140.249>, <106.9975, -138.811>//circle
				<106.9975, -138.811>, <106.9975, -137.37300000000002>, <108.163, -136.2075>, <109.601, -136.2075>//circle
				<90.551, -98.1075>, <91.989, -98.1075>, <93.1545, -99.273>, <93.1545, -100.711>//circle
				<93.1545, -100.711>, <93.1545, -102.149>, <91.989, -103.3145>, <90.551, -103.3145>//circle
				<90.551, -103.3145>, <89.113, -103.3145>, <87.9475, -102.149>, <87.9475, -100.711>//circle
				<87.9475, -100.711>, <87.9475, -99.273>, <89.113, -98.1075>, <90.551, -98.1075>//circle
				<103.251, -98.1075>, <104.68900000000001, -98.1075>, <105.8545, -99.273>, <105.8545, -100.711>//circle
				<105.8545, -100.711>, <105.8545, -102.149>, <104.68900000000001, -103.3145>, <103.251, -103.3145>//circle
				<103.251, -103.3145>, <101.813, -103.3145>, <100.64750000000001, -102.149>, <100.64750000000001, -100.711>//circle
				<100.64750000000001, -100.711>, <100.64750000000001, -99.273>, <101.813, -98.1075>, <103.251, -98.1075>//circle
				<109.601, -98.1075>, <111.039, -98.1075>, <112.2045, -99.273>, <112.2045, -100.711>//circle
				<112.2045, -100.711>, <112.2045, -102.149>, <111.039, -103.3145>, <109.601, -103.3145>//circle
				<109.601, -103.3145>, <108.163, -103.3145>, <106.9975, -102.149>, <106.9975, -100.711>//circle
				<106.9975, -100.711>, <106.9975, -99.273>, <108.163, -98.1075>, <109.601, -98.1075>//circle
				<90.551, -110.8075>, <91.989, -110.8075>, <93.1545, -111.973>, <93.1545, -113.411>//circle
				<93.1545, -113.411>, <93.1545, -114.849>, <91.989, -116.0145>, <90.551, -116.0145>//circle
				<90.551, -116.0145>, <89.113, -116.0145>, <87.9475, -114.849>, <87.9475, -113.411>//circle
				<87.9475, -113.411>, <87.9475, -111.973>, <89.113, -110.8075>, <90.551, -110.8075>//circle
				<103.251, -110.8075>, <104.68900000000001, -110.8075>, <105.8545, -111.973>, <105.8545, -113.411>//circle
				<105.8545, -113.411>, <105.8545, -114.849>, <104.68900000000001, -116.0145>, <103.251, -116.0145>//circle
				<103.251, -116.0145>, <101.813, -116.0145>, <100.64750000000001, -114.849>, <100.64750000000001, -113.411>//circle
				<100.64750000000001, -113.411>, <100.64750000000001, -111.973>, <101.813, -110.8075>, <103.251, -110.8075>//circle
				<109.601, -110.8075>, <111.039, -110.8075>, <112.2045, -111.973>, <112.2045, -113.411>//circle
				<112.2045, -113.411>, <112.2045, -114.849>, <111.039, -116.0145>, <109.601, -116.0145>//circle
				<109.601, -116.0145>, <108.163, -116.0145>, <106.9975, -114.849>, <106.9975, -113.411>//circle
				<106.9975, -113.411>, <106.9975, -111.973>, <108.163, -110.8075>, <109.601, -110.8075>//circle
				<136.271, -123.50750000000001>, <137.70899999999997, -123.50750000000001>, <138.87449999999998, -124.673>, <138.87449999999998, -126.111>//circle
				<138.87449999999998, -126.111>, <138.87449999999998, -127.549>, <137.70899999999997, -128.7145>, <136.271, -128.7145>//circle
				<136.271, -128.7145>, <134.833, -128.7145>, <133.6675, -127.549>, <133.6675, -126.111>//circle
				<133.6675, -126.111>, <133.6675, -124.673>, <134.833, -123.50750000000001>, <136.271, -123.50750000000001>//circle
				<148.971, -123.50750000000001>, <150.409, -123.50750000000001>, <151.5745, -124.673>, <151.5745, -126.111>//circle
				<151.5745, -126.111>, <151.5745, -127.549>, <150.409, -128.7145>, <148.971, -128.7145>//circle
				<148.971, -128.7145>, <147.53300000000002, -128.7145>, <146.3675, -127.549>, <146.3675, -126.111>//circle
				<146.3675, -126.111>, <146.3675, -124.673>, <147.53300000000002, -123.50750000000001>, <148.971, -123.50750000000001>//circle
				<155.321, -123.50750000000001>, <156.759, -123.50750000000001>, <157.9245, -124.673>, <157.9245, -126.111>//circle
				<157.9245, -126.111>, <157.9245, -127.549>, <156.759, -128.7145>, <155.321, -128.7145>//circle
				<155.321, -128.7145>, <153.883, -128.7145>, <152.7175, -127.549>, <152.7175, -126.111>//circle
				<152.7175, -126.111>, <152.7175, -124.673>, <153.883, -123.50750000000001>, <155.321, -123.50750000000001>//circle
				<136.271, -136.2075>, <137.70899999999997, -136.2075>, <138.87449999999998, -137.37300000000002>, <138.87449999999998, -138.811>//circle
				<138.87449999999998, -138.811>, <138.87449999999998, -140.249>, <137.70899999999997, -141.4145>, <136.271, -141.4145>//circle
				<136.271, -141.4145>, <134.833, -141.4145>, <133.6675, -140.249>, <133.6675, -138.811>//circle
				<133.6675, -138.811>, <133.6675, -137.37300000000002>, <134.833, -136.2075>, <136.271, -136.2075>//circle
				<148.971, -136.2075>, <150.409, -136.2075>, <151.5745, -137.37300000000002>, <151.5745, -138.811>//circle
				<151.5745, -138.811>, <151.5745, -140.249>, <150.409, -141.4145>, <148.971, -141.4145>//circle
				<148.971, -141.4145>, <147.53300000000002, -141.4145>, <146.3675, -140.249>, <146.3675, -138.811>//circle
				<146.3675, -138.811>, <146.3675, -137.37300000000002>, <147.53300000000002, -136.2075>, <148.971, -136.2075>//circle
				<155.321, -136.2075>, <156.759, -136.2075>, <157.9245, -137.37300000000002>, <157.9245, -138.811>//circle
				<157.9245, -138.811>, <157.9245, -140.249>, <156.759, -141.4145>, <155.321, -141.4145>//circle
				<155.321, -141.4145>, <153.883, -141.4145>, <152.7175, -140.249>, <152.7175, -138.811>//circle
				<152.7175, -138.811>, <152.7175, -137.37300000000002>, <153.883, -136.2075>, <155.321, -136.2075>//circle
				<136.271, -98.1075>, <137.70899999999997, -98.1075>, <138.87449999999998, -99.273>, <138.87449999999998, -100.711>//circle
				<138.87449999999998, -100.711>, <138.87449999999998, -102.149>, <137.70899999999997, -103.3145>, <136.271, -103.3145>//circle
				<136.271, -103.3145>, <134.833, -103.3145>, <133.6675, -102.149>, <133.6675, -100.711>//circle
				<133.6675, -100.711>, <133.6675, -99.273>, <134.833, -98.1075>, <136.271, -98.1075>//circle
				<148.971, -98.1075>, <150.409, -98.1075>, <151.5745, -99.273>, <151.5745, -100.711>//circle
				<151.5745, -100.711>, <151.5745, -102.149>, <150.409, -103.3145>, <148.971, -103.3145>//circle
				<148.971, -103.3145>, <147.53300000000002, -103.3145>, <146.3675, -102.149>, <146.3675, -100.711>//circle
				<146.3675, -100.711>, <146.3675, -99.273>, <147.53300000000002, -98.1075>, <148.971, -98.1075>//circle
				<155.321, -98.1075>, <156.759, -98.1075>, <157.9245, -99.273>, <157.9245, -100.711>//circle
				<157.9245, -100.711>, <157.9245, -102.149>, <156.759, -103.3145>, <155.321, -103.3145>//circle
				<155.321, -103.3145>, <153.883, -103.3145>, <152.7175, -102.149>, <152.7175, -100.711>//circle
				<152.7175, -100.711>, <152.7175, -99.273>, <153.883, -98.1075>, <155.321, -98.1075>//circle
				<136.271, -110.8075>, <137.70899999999997, -110.8075>, <138.87449999999998, -111.973>, <138.87449999999998, -113.411>//circle
				<138.87449999999998, -113.411>, <138.87449999999998, -114.849>, <137.70899999999997, -116.0145>, <136.271, -116.0145>//circle
				<136.271, -116.0145>, <134.833, -116.0145>, <133.6675, -114.849>, <133.6675, -113.411>//circle
				<133.6675, -113.411>, <133.6675, -111.973>, <134.833, -110.8075>, <136.271, -110.8075>//circle
				<148.971, -110.8075>, <150.409, -110.8075>, <151.5745, -111.973>, <151.5745, -113.411>//circle
				<151.5745, -113.411>, <151.5745, -114.849>, <150.409, -116.0145>, <148.971, -116.0145>//circle
				<148.971, -116.0145>, <147.53300000000002, -116.0145>, <146.3675, -114.849>, <146.3675, -113.411>//circle
				<146.3675, -113.411>, <146.3675, -111.973>, <147.53300000000002, -110.8075>, <148.971, -110.8075>//circle
				<155.321, -110.8075>, <156.759, -110.8075>, <157.9245, -111.973>, <157.9245, -113.411>//circle
				<157.9245, -113.411>, <157.9245, -114.849>, <156.759, -116.0145>, <155.321, -116.0145>//circle
				<155.321, -116.0145>, <153.883, -116.0145>, <152.7175, -114.849>, <152.7175, -113.411>//circle
				<152.7175, -113.411>, <152.7175, -111.973>, <153.883, -110.8075>, <155.321, -110.8075>//circle
				<170.561, -123.50750000000001>, <171.999, -123.50750000000001>, <173.1645, -124.673>, <173.1645, -126.111>//circle
				<173.1645, -126.111>, <173.1645, -127.549>, <171.999, -128.7145>, <170.561, -128.7145>//circle
				<170.561, -128.7145>, <169.12300000000002, -128.7145>, <167.9575, -127.549>, <167.9575, -126.111>//circle
				<167.9575, -126.111>, <167.9575, -124.673>, <169.12300000000002, -123.50750000000001>, <170.561, -123.50750000000001>//circle
				<183.261, -123.50750000000001>, <184.69899999999998, -123.50750000000001>, <185.8645, -124.673>, <185.8645, -126.111>//circle
				<185.8645, -126.111>, <185.8645, -127.549>, <184.69899999999998, -128.7145>, <183.261, -128.7145>//circle
				<183.261, -128.7145>, <181.823, -128.7145>, <180.6575, -127.549>, <180.6575, -126.111>//circle
				<180.6575, -126.111>, <180.6575, -124.673>, <181.823, -123.50750000000001>, <183.261, -123.50750000000001>//circle
				<189.611, -123.50750000000001>, <191.04899999999998, -123.50750000000001>, <192.2145, -124.673>, <192.2145, -126.111>//circle
				<192.2145, -126.111>, <192.2145, -127.549>, <191.04899999999998, -128.7145>, <189.611, -128.7145>//circle
				<189.611, -128.7145>, <188.173, -128.7145>, <187.0075, -127.549>, <187.0075, -126.111>//circle
				<187.0075, -126.111>, <187.0075, -124.673>, <188.173, -123.50750000000001>, <189.611, -123.50750000000001>//circle
				<170.561, -136.2075>, <171.999, -136.2075>, <173.1645, -137.37300000000002>, <173.1645, -138.811>//circle
				<173.1645, -138.811>, <173.1645, -140.249>, <171.999, -141.4145>, <170.561, -141.4145>//circle
				<170.561, -141.4145>, <169.12300000000002, -141.4145>, <167.9575, -140.249>, <167.9575, -138.811>//circle
				<167.9575, -138.811>, <167.9575, -137.37300000000002>, <169.12300000000002, -136.2075>, <170.561, -136.2075>//circle
				<183.261, -136.2075>, <184.69899999999998, -136.2075>, <185.8645, -137.37300000000002>, <185.8645, -138.811>//circle
				<185.8645, -138.811>, <185.8645, -140.249>, <184.69899999999998, -141.4145>, <183.261, -141.4145>//circle
				<183.261, -141.4145>, <181.823, -141.4145>, <180.6575, -140.249>, <180.6575, -138.811>//circle
				<180.6575, -138.811>, <180.6575, -137.37300000000002>, <181.823, -136.2075>, <183.261, -136.2075>//circle
				<189.611, -136.2075>, <191.04899999999998, -136.2075>, <192.2145, -137.37300000000002>, <192.2145, -138.811>//circle
				<192.2145, -138.811>, <192.2145, -140.249>, <191.04899999999998, -141.4145>, <189.611, -141.4145>//circle
				<189.611, -141.4145>, <188.173, -141.4145>, <187.0075, -140.249>, <187.0075, -138.811>//circle
				<187.0075, -138.811>, <187.0075, -137.37300000000002>, <188.173, -136.2075>, <189.611, -136.2075>//circle
				<170.561, -98.1075>, <171.999, -98.1075>, <173.1645, -99.273>, <173.1645, -100.711>//circle
				<173.1645, -100.711>, <173.1645, -102.149>, <171.999, -103.3145>, <170.561, -103.3145>//circle
				<170.561, -103.3145>, <169.12300000000002, -103.3145>, <167.9575, -102.149>, <167.9575, -100.711>//circle
				<167.9575, -100.711>, <167.9575, -99.273>, <169.12300000000002, -98.1075>, <170.561, -98.1075>//circle
				<183.261, -98.1075>, <184.69899999999998, -98.1075>, <185.8645, -99.273>, <185.8645, -100.711>//circle
				<185.8645, -100.711>, <185.8645, -102.149>, <184.69899999999998, -103.3145>, <183.261, -103.3145>//circle
				<183.261, -103.3145>, <181.823, -103.3145>, <180.6575, -102.149>, <180.6575, -100.711>//circle
				<180.6575, -100.711>, <180.6575, -99.273>, <181.823, -98.1075>, <183.261, -98.1075>//circle
				<189.611, -98.1075>, <191.04899999999998, -98.1075>, <192.2145, -99.273>, <192.2145, -100.711>//circle
				<192.2145, -100.711>, <192.2145, -102.149>, <191.04899999999998, -103.3145>, <189.611, -103.3145>//circle
				<189.611, -103.3145>, <188.173, -103.3145>, <187.0075, -102.149>, <187.0075, -100.711>//circle
				<187.0075, -100.711>, <187.0075, -99.273>, <188.173, -98.1075>, <189.611, -98.1075>//circle
				<170.561, -110.8075>, <171.999, -110.8075>, <173.1645, -111.973>, <173.1645, -113.411>//circle
				<173.1645, -113.411>, <173.1645, -114.849>, <171.999, -116.0145>, <170.561, -116.0145>//circle
				<170.561, -116.0145>, <169.12300000000002, -116.0145>, <167.9575, -114.849>, <167.9575, -113.411>//circle
				<167.9575, -113.411>, <167.9575, -111.973>, <169.12300000000002, -110.8075>, <170.561, -110.8075>//circle
				<183.261, -110.8075>, <184.69899999999998, -110.8075>, <185.8645, -111.973>, <185.8645, -113.411>//circle
				<185.8645, -113.411>, <185.8645, -114.849>, <184.69899999999998, -116.0145>, <183.261, -116.0145>//circle
				<183.261, -116.0145>, <181.823, -116.0145>, <180.6575, -114.849>, <180.6575, -113.411>//circle
				<180.6575, -113.411>, <180.6575, -111.973>, <181.823, -110.8075>, <183.261, -110.8075>//circle
				<189.611, -110.8075>, <191.04899999999998, -110.8075>, <192.2145, -111.973>, <192.2145, -113.411>//circle
				<192.2145, -113.411>, <192.2145, -114.849>, <191.04899999999998, -116.0145>, <189.611, -116.0145>//circle
				<189.611, -116.0145>, <188.173, -116.0145>, <187.0075, -114.849>, <187.0075, -113.411>//circle
				<187.0075, -113.411>, <187.0075, -111.973>, <188.173, -110.8075>, <189.611, -110.8075>//circle
				<119.761, -109.601>, <121.164, -109.601>, <122.301, -110.738>, <122.301, -112.141>//circle
				<122.301, -112.141>, <122.301, -113.54400000000001>, <121.164, -114.68100000000001>, <119.761, -114.68100000000001>//circle
				<119.761, -114.68100000000001>, <118.35799999999999, -114.68100000000001>, <117.22099999999999, -113.54400000000001>, <117.22099999999999, -112.141>//circle
				<117.22099999999999, -112.141>, <117.22099999999999, -110.738>, <118.35799999999999, -109.601>, <119.761, -109.601>//circle
				<119.761, -124.841>, <121.164, -124.841>, <122.301, -125.978>, <122.301, -127.381>//circle
				<122.301, -127.381>, <122.301, -128.784>, <121.164, -129.921>, <119.761, -129.921>//circle
				<119.761, -129.921>, <118.35799999999999, -129.921>, <117.22099999999999, -128.784>, <117.22099999999999, -127.381>//circle
				<117.22099999999999, -127.381>, <117.22099999999999, -125.978>, <118.35799999999999, -124.841>, <119.761, -124.841>//circle
				<33.973, -166.6875>, <35.411, -166.6875>, <36.576499999999996, -167.853>, <36.576499999999996, -169.291>//circle
				<36.576499999999996, -169.291>, <36.576499999999996, -170.72899999999998>, <35.411, -171.8945>, <33.973, -171.8945>//circle
				<33.973, -171.8945>, <32.535, -171.8945>, <31.369500000000002, -170.72899999999998>, <31.369500000000002, -169.291>//circle
				<31.369500000000002, -169.291>, <31.369500000000002, -167.853>, <32.535, -166.6875>, <33.973, -166.6875>//circle
				<70.231, -202.9455>, <71.669, -202.9455>, <72.83449999999999, -204.11100000000002>, <72.83449999999999, -205.549>//circle
				<72.83449999999999, -205.549>, <72.83449999999999, -206.987>, <71.669, -208.1525>, <70.231, -208.1525>//circle
				<70.231, -208.1525>, <68.79299999999999, -208.1525>, <67.6275, -206.987>, <67.6275, -205.549>//circle
				<67.6275, -205.549>, <67.6275, -204.11100000000002>, <68.79299999999999, -202.9455>, <70.231, -202.9455>//circle
				<119.761, -216.2175>, <121.199, -216.2175>, <122.36449999999999, -217.383>, <122.36449999999999, -218.821>//circle
				<122.36449999999999, -218.821>, <122.36449999999999, -220.259>, <121.199, -221.4245>, <119.761, -221.4245>//circle
				<119.761, -221.4245>, <118.323, -221.4245>, <117.1575, -220.259>, <117.1575, -218.821>//circle
				<117.1575, -218.821>, <117.1575, -217.383>, <118.323, -216.2175>, <119.761, -216.2175>//circle
				<169.291, -202.9455>, <170.72899999999998, -202.9455>, <171.8945, -204.11100000000002>, <171.8945, -205.549>//circle
				<171.8945, -205.549>, <171.8945, -206.987>, <170.72899999999998, -208.1525>, <169.291, -208.1525>//circle
				<169.291, -208.1525>, <167.853, -208.1525>, <166.6875, -206.987>, <166.6875, -205.549>//circle
				<166.6875, -205.549>, <166.6875, -204.11100000000002>, <167.853, -202.9455>, <169.291, -202.9455>//circle
				<205.549, -166.6875>, <206.987, -166.6875>, <208.1525, -167.853>, <208.1525, -169.291>//circle
				<208.1525, -169.291>, <208.1525, -170.72899999999998>, <206.987, -171.8945>, <205.549, -171.8945>//circle
				<205.549, -171.8945>, <204.11100000000002, -171.8945>, <202.9455, -170.72899999999998>, <202.9455, -169.291>//circle
				<202.9455, -169.291>, <202.9455, -167.853>, <204.11100000000002, -166.6875>, <205.549, -166.6875>//circle
				
				rotate <-90.0, 0.0, 0.0>
		
			}
		
		}
		
		prism {
			bezier_spline
			0.0001, -5.0, 144
			<4.826, -3.3019999999999996>, <5.667999999999999, -3.3019999999999996>, <6.35, -3.9839999999999995>, <6.35, -4.826>//circle
			<6.35, -4.826>, <6.35, -5.667999999999999>, <5.667999999999999, -6.35>, <4.826, -6.35>//circle
			<4.826, -6.35>, <3.9839999999999995, -6.35>, <3.3019999999999996, -5.667999999999999>, <3.3019999999999996, -4.826>//circle
			<3.3019999999999996, -4.826>, <3.3019999999999996, -3.9839999999999995>, <3.9839999999999995, -3.3019999999999996>, <4.826, -3.3019999999999996>//circle
			<234.696, -3.3019999999999987>, <235.538, -3.3019999999999987>, <236.22, -3.9839999999999995>, <236.22, -4.826>//circle
			<236.22, -4.826>, <236.22, -5.667999999999999>, <235.538, -6.3500000000000005>, <234.696, -6.3500000000000005>//circle
			<234.696, -6.3500000000000005>, <233.85399999999998, -6.3500000000000005>, <233.172, -5.667999999999999>, <233.172, -4.826>//circle
			<233.172, -4.826>, <233.172, -3.9839999999999995>, <233.85399999999998, -3.3019999999999987>, <234.696, -3.3019999999999987>//circle
			<4.826, -233.172>, <5.667999999999999, -233.172>, <6.35, -233.85399999999998>, <6.35, -234.696>//circle
			<6.35, -234.696>, <6.35, -235.538>, <5.667999999999999, -236.22>, <4.826, -236.22>//circle
			<4.826, -236.22>, <3.9839999999999995, -236.22>, <3.3019999999999996, -235.538>, <3.3019999999999996, -234.696>//circle
			<3.3019999999999996, -234.696>, <3.3019999999999996, -233.85399999999998>, <3.9839999999999995, -233.172>, <4.826, -233.172>//circle
			<234.696, -233.172>, <235.538, -233.172>, <236.22, -233.85399999999998>, <236.22, -234.696>//circle
			<236.22, -234.696>, <236.22, -235.538>, <235.538, -236.22>, <234.696, -236.22>//circle
			<234.696, -236.22>, <233.85399999999998, -236.22>, <233.172, -235.538>, <233.172, -234.696>//circle
			<233.172, -234.696>, <233.172, -233.85399999999998>, <233.85399999999998, -233.172>, <234.696, -233.172>//circle
			<4.826, -118.237>, <5.667999999999999, -118.237>, <6.35, -118.919>, <6.35, -119.761>//circle
			<6.35, -119.761>, <6.35, -120.603>, <5.667999999999999, -121.285>, <4.826, -121.285>//circle
			<4.826, -121.285>, <3.9839999999999995, -121.285>, <3.3019999999999996, -120.603>, <3.3019999999999996, -119.761>//circle
			<3.3019999999999996, -119.761>, <3.3019999999999996, -118.919>, <3.9839999999999995, -118.237>, <4.826, -118.237>//circle
			<119.761, -118.237>, <120.603, -118.237>, <121.285, -118.919>, <121.285, -119.761>//circle
			<121.285, -119.761>, <121.285, -120.603>, <120.603, -121.285>, <119.761, -121.285>//circle
			<119.761, -121.285>, <118.919, -121.285>, <118.237, -120.603>, <118.237, -119.761>//circle
			<118.237, -119.761>, <118.237, -118.919>, <118.919, -118.237>, <119.761, -118.237>//circle
			<234.696, -118.237>, <235.538, -118.237>, <236.22, -118.919>, <236.22, -119.761>//circle
			<236.22, -119.761>, <236.22, -120.603>, <235.538, -121.285>, <234.696, -121.285>//circle
			<234.696, -121.285>, <233.85399999999998, -121.285>, <233.172, -120.603>, <233.172, -119.761>//circle
			<233.172, -119.761>, <233.172, -118.919>, <233.85399999999998, -118.237>, <234.696, -118.237>//circle
			<119.761, -233.172>, <120.603, -233.172>, <121.285, -233.85399999999998>, <121.285, -234.696>//circle
			<121.285, -234.696>, <121.285, -235.538>, <120.603, -236.22>, <119.761, -236.22>//circle
			<119.761, -236.22>, <118.919, -236.22>, <118.237, -235.538>, <118.237, -234.696>//circle
			<118.237, -234.696>, <118.237, -233.85399999999998>, <118.919, -233.172>, <119.761, -233.172>//circle
			<119.761, -3.3019999999999987>, <120.603, -3.3019999999999987>, <121.285, -3.9839999999999995>, <121.285, -4.826>//circle
			<121.285, -4.826>, <121.285, -5.667999999999999>, <120.603, -6.3500000000000005>, <119.761, -6.3500000000000005>//circle
			<119.761, -6.3500000000000005>, <118.919, -6.3500000000000005>, <118.237, -5.667999999999999>, <118.237, -4.826>//circle
			<118.237, -4.826>, <118.237, -3.9839999999999995>, <118.919, -3.3019999999999987>, <119.761, -3.3019999999999987>//circle
			
			rotate <-90.0, 0.0, 0.0>
	
		}
	
	}
	
	pigment { color rgb <0.000, 0.000, 0.000> }
	
	translate <0.0, 0.0, 33.2>
}

//----- X_Axis024 -----
//----- Y_Axis024 -----
//----- Z_Axis024 -----
//----- XY_Plane024 -----
//----- XZ_Plane024 -----
//----- YZ_Plane024 -----
//----- Screw_upper_left -----
object { Screw_upper_left_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_middle_left -----
object { Screw_middle_left_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_bottom_left -----
object { Screw_bottom_left_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_bottom_middle -----
object { Screw_bottom_middle_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_bottom_right -----
object { Screw_bottom_right_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_centre -----
object { Screw_centre_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_upper_middle -----
object { Screw_upper_middle_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_middle_right -----
object { Screw_middle_right_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Screw_upper_right -----
object { Screw_upper_right_mesh
		pigment { color rgb <0.122, 0.122, 0.122> }

}

//----- Inner_frame -----
object { Inner_frame_mesh
		pigment { color rgb <0.149, 0.149, 0.149> }

}

//----- X_Axis025 -----
//----- Y_Axis025 -----
//----- Z_Axis025 -----
//----- XY_Plane025 -----
//----- XZ_Plane025 -----
//----- YZ_Plane025 -----
//----- Front_glass -----
union {

	//----- Pad003 -----
	union {
	
		prism {
			bezier_spline
			0, -3.0, 16
			<-5.239, 5.239>, <-5.239, 5.239>, <244.761, 5.239>, <244.761, 5.239>//line
			<244.761, 5.239>, <244.761, 5.239>, <244.761, -244.761>, <244.761, -244.761>//line
			<244.761, -244.761>, <244.761, -244.761>, <-5.239, -244.761>, <-5.239, -244.761>//line
			<-5.239, -244.761>, <-5.239, -244.761>, <-5.239, 5.239>, <-5.239, 5.239>//line
			
			rotate <-90.0, 0.0, 0.0>
	
		}
	
	}
	
	pigment { color rgb <0.000, 0.000, 0.000> transmit 0.85 }
	finish {
		ambient rgb<0.086, 0.086, 0.086>
		
		phong 1.00 phong_size 50.0 
	}
	
	translate <0.0, 0.0, 46.1>
}

//----- X_Axis026 -----
//----- Y_Axis026 -----
//----- Z_Axis026 -----
//----- XY_Plane026 -----
//----- XZ_Plane026 -----
//----- YZ_Plane026 -----
//----- Outer_frame -----
object { Outer_frame_mesh
		pigment { color rgb <0.078, 0.078, 0.078> }

}

//----- X_Axis027 -----
//----- Y_Axis027 -----
//----- Z_Axis027 -----
//----- XY_Plane027 -----
//----- XZ_Plane027 -----
//----- YZ_Plane027 -----
//----- PovProject -----
//----- Body_View -----
//----- Body001_View -----
//----- Part__Feature036_View -----
//----- Part__Feature037_View -----
//----- Part__Feature038_View -----
//----- Part__Feature039_View -----
//----- Part__Feature040_View -----
//----- Part__Feature041_View -----
//----- Part__Feature042_View -----
//----- Part__Feature043_View -----
//----- Part__Feature044_View -----
//----- Body002_View -----
//----- Body004_View -----
//----- AreaLight -----
light_source { <0, 0, 0>
	color rgb<1.0, 1.0, 1.0>
	area_light
	<50.0, 0, 0>, <0, 50.0, 0>
	5, 5
	adaptive 1
	jitter
	translate <125.0, -125.0, 400.0>
}
