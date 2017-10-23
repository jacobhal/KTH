<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Spec extends Model
{
	protected $primaryKey = 'user_id';
    /**
	 * The database table used by the model.
	 *
	 * @var string
	 */
	protected $table = 'specs';

	/**
	 * The guarded fields for specifications.
	 * 
	 * @var array(string)
	 */
	protected $guarded = array();


	/**
	 * Get the User associated with these specifications
	 */
	public function user() {
		return $this->belongsTo('App\Models\User', 'user_id');
	}

	
}
