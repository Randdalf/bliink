$modelname	"props\pallet.mdl"
$cdmaterials	"models\props\"
$scale 50

$body mybody	"pallet.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"pallet.smd"

$collisionmodel	"pallet.smd" { $concave }