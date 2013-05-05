$modelname	"props\exhaust.mdl"
$cdmaterials	"models\props\"
$scale 100

$body mybody	"exhaust.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"exhaust.smd"

$collisionmodel	"exhaust.smd" { $concave }