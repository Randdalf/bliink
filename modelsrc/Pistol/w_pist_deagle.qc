$modelname "w_bliink_pistol.mdl"
$scale 1.00
$cdmaterials "models"

$body "Body" "w_pist_deagle.smd"

$sequence "Idle" "J:\Work\Uni Work\Third Year\Games Project\Models\Pistol\w_pist_deagle.smd" fps 30 ACT_IDLE 1

$surfaceprop "metal"

$collisionmodel "J:\Work\Uni Work\Third Year\Games Project\Models\Pistol\w_pist_deagle.smd" {
	$concave
	$mass 100.000
}
