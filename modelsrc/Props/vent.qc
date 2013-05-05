$modelname	"props\vent.mdl"
$cdmaterials	"models\props\"
$scale 50

$body mybody	"vent.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"vent.smd"

$collisionmodel	"vent.smd" { $concave }