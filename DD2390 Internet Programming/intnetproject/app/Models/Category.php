<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Category extends Model
{
    /**
	 * The database table used by the model.
	 *
	 * @var string
	 */
	protected $table = 'categories';

	/**
	 * The mass assignable fields for pm.
	 * 
	 * @var array(string)
	 */
	protected $fillable = array('name', 'parent_id');

	/**
	 * Get the posts in this category
	 */
	public function posts() {
		return $this->hasMany('App\Models\Post');
	}

	/**
	 * Get the games associated with this category
	 */
	public function games() {
		return $this->hasMany('App\Models\Game')->orderBy('title', 'asc');
	}

	
}
