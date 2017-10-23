<?php

use Illuminate\Database\Seeder;
use Illuminate\Database\Eloquent\Model;
use Intnetproject\User;

class UserTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
	{
	    DB::table('users')->delete();
	    User::create(array(
	    	'id'  			=> 1,
	        'name'     		=> 'Jacob Hallman',
	        'username' 		=> 'jacke20',
	        'email'			=> 'jackeaik@hotmail.com',
	        'privileges'    => 'admin',
	        'password' 		=> Hash::make('123'),
	    ));
	}

}