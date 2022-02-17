from flask import Response, request
from functools import wraps
import jwt

token_missing = "token is missing"
token_not_valid = "token not valid"
token_unauthorized = "unauthorized"

role_admin = "ADMIN"
role_restaurant = "RESTAURANT"
role_user = "USER"


def token_required_admin(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        token = request.args.get('token')
        print(token)
        if not token:
            return f'{token_missing}', 403
        try:
            data = jwt.decode(token, options={"verify_signature": False})
            role = data["http://schemas.microsoft.com/ws/2008/06/identity/claims/role"]
            if role != role_admin:
                return f'{token_unauthorized}', 401
        except:
            return f'{token_not_valid}', 401

        return f(*args, **kwargs)

    return decorated


def token_required_restaurant(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        token = request.args.get('token')
        print(token)
        if not token:
            return f'{token_missing}', 403
        try:
            data = jwt.decode(token, options={"verify_signature": False})
            role = data["http://schemas.microsoft.com/ws/2008/06/identity/claims/role"]
            if role != role_admin and role != role_restaurant:
                return f'{token_unauthorized}', 401
        except:
            return f'{token_not_valid}', 401

        return f(*args, **kwargs)

    return decorated


def token_required_user(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        token = request.args.get('token')
        print(token)
        if not token:
            return f'{token_missing}', 403
        try:
            data = jwt.decode(token, options={"verify_signature": False})
            role = data["http://schemas.microsoft.com/ws/2008/06/identity/claims/role"]
            if role != role_admin and role != role_user:
                return f'{token_unauthorized}', 401
        except:
            return f'{token_not_valid}', 401

        return f(*args, **kwargs)

    return decorated
