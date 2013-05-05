$modelname	"props\pallet.mdl"
$cdmaterials	"models\props\"
$scale 200

$body mybody	"pallet.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"pallet.smd"

$collisionmodel	"pallet.smd" { $concave }