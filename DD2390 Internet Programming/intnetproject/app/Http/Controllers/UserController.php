<?php

namespace App\Http\Controllers;

use Auth, Input, Redirect, View, Log, Hash;
use Illuminate\Http\Request;
use App\Models\User;
use App\Models\Spec;
use Validator;
use App\Http\Controllers\Controller;
use Illuminate\Foundation\Auth\ThrottlesLogins;
use Illuminate\Foundation\Auth\AuthenticatesAndRegistersUsers;

class UserController extends Controller {
    
    /**
     * Get the profile page for user with specified id.
     */
    public function getProfile($id) {
    	try {
            $user = User::find($id);
            $specifications = $user->specs;
        } catch (ModelNotFoundException $e){
            Log::error('No category found!'); // This should never happen
        }

        $view = View::make('user.profile')
                ->with('user', $user)
                ->with('specs', $specifications);
        return $view;
    }

    /**
     * Get settings page for logged in user.
     */
    public function getSettings() {
        try {
            $user = Auth::user();
            $settings = Auth::user()->specs;
        } catch (ModelNotFoundException $e){
            Log::error('No user found!'); // This should never happen
        }
        return View::make('user.settings')
            ->with('user', $user)
            ->with('settings', $settings);
    }

    /**
     * Change the settings for logged in user.
     */
    public function postSettings(Request $request) {
        $userid = Auth::user()->id;
        $specs = Spec::where('user_id', '=', $userid)->first();

        $data = Input::all();

        $specs->cpu = $data['cpu'];
        $specs->gpu = $data['gpu'];
        $specs->power = $data['power'];
        $specs->motherboard = $data['motherboard'];
        $specs->computercase = $data['computercase'];
        $specs->ram = $data['ram'];
        $specs->hd1 = $data['hd1'];
        $specs->hd2 = $data['hd2'];
        $specs->os = $data['os'];

        $specs->save();

    
        return Redirect::back()
            ->with('success', 'Your information has been updated!');
    }
}